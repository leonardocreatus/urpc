#include "client.hpp"

Client::Client(int port, std::string ip, int payload_size, int timeout, int window){
    srand(time(NULL));
    this->port = port;
    this->ip = ip;
    this->payload_size = payload_size;
    this->timeout = timeout;
    this->window = window;
    if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
        // std::cout << "socket error" << std::endl;
        exit(1);
    }

    memset((char *) &si_other, 0, sizeof(si_other));
	
    si_other.sin_family = AF_INET;
	si_other.sin_port = htons(this->port);   

    if (inet_aton(this->ip.c_str() , &si_other.sin_addr) == 0){
        // std::cout << "inet_aton error" << std::endl;
        exit(1);
    }
}

Client::~Client(){
    close(s);
}

void Client::send(std::string msg){
    // std::cout << "Client send start" << std::endl;
    int parts = ceil(msg.length() / (double)this->payload_size);
    // std::cout << "parts: " << parts << std::endl;
    std::vector<int> noAcks;
    int random = rand();
    omp_set_num_threads(16);

    

    for(int send = 0; send < parts; send += this->window){
        #pragma omp parallel for
        for(int i = 0 ; i < this->window; i++){
            if(send + i >= parts) continue;
            // std::cout << "send: " << send + i << std::endl;
            std::string payload = msg.substr((send + i) * this->payload_size, std::min(this->payload_size, (int)msg.length() - ((send + i) * this->payload_size)));
            char buf[sizeof(struct data_s) + this->payload_size];
            struct data_s *ptr = (struct data_s *)buf;
            
            ptr->parts = parts;
            ptr->seq = i + send;
            ptr->tid = random;

            char *data = (char *)buf + sizeof(struct data_s);
            memcpy(data, payload.data(), payload.length());
            if (sendto(s, buf, sizeof(struct data_s) + payload.size() , 0 , (struct sockaddr *) &si_other, slen) == -1){
                // std::cout << "sendto error" << std::endl;
                exit(1);
            }else {
                // std::cout << "sendto success, " << i + send << std::endl;
            }

            struct timeval tv;
            tv.tv_sec = 0;
            tv.tv_usec = this->timeout * 1000;
            setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
            int recv_len;


            socklen_t len = sizeof(si_other);
            if ((recv_len = recvfrom(s, buf, sizeof(struct data_s) + this->payload_size, 0, (struct sockaddr *) &si_other, &len)) == -1){
                // std::cout << "recvfrom error, " << ptr->seq << ", " << send + i << std::endl;
                noAcks.push_back(send + i);
                continue;
            }
            
            if(ptr->seq != send + i){
                // std::cout << "recvfrom error, " << ptr->seq << ", " << send + i << std::endl;
                noAcks.push_back(send + i);
                continue;
            }

            // std::cout << "recvfrom success, " << i + send << std::endl;

            if(ptr->seq != i + send){
                // std::cout << "seq error, " << ptr->seq << ", " << send + i << std::endl;
                noAcks.push_back(send + i);
            }
        }
    }

    // std::cout << "noAcks size: " << noAcks.size() << std::endl;

    int count = 0;
    while(noAcks.size() > 0){
        std::vector<int> newNoAcks;
        int noAckCount = 0;
        
        #pragma omp parallel for shared(noAckCount)
        for(int i = 0; i < noAcks.size(); i++){
            if(noAcks.size() == 0) continue;
            // std::cout << "resend, " << noAcks[i] << std::endl;
            std::string payload = msg.substr(noAcks[i] * this->payload_size, std::min(this->payload_size, (int)msg.length() - (noAcks[i] * this->payload_size)));
            char buf[sizeof(struct data_s) + this->payload_size];
            struct data_s *ptr = (struct data_s *)buf;
            
            ptr->parts = parts;
            ptr->seq = noAcks[i];
            ptr->tid = random;

            char *data = (char *)buf + sizeof(struct data_s);
            memcpy(data, payload.data(), payload.length());
            if (sendto(s, buf, sizeof(struct data_s) + payload.size() , 0 , (struct sockaddr *) &si_other, slen) == -1){
                // std::cout << "no ack -> sendto error, " << noAcks[i] << std::endl;
                exit(1);
            }

            struct timeval tv;
            tv.tv_sec = 0;
            tv.tv_usec = this->timeout * 1000; // 10ms
            setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

            int recv_len;
            socklen_t len = sizeof(si_other);
            if ((recv_len = recvfrom(s, buf, sizeof(struct data_s) + this->payload_size, 0, (struct sockaddr *) &si_other, &len)) == -1){
                // std::cout << "no ack -> recvfrom error, " << noAcks[i] << std::endl;
                
                noAckCount++;
                // std::cout << "noAckCount: " << noAckCount << std::endl;

                if(noAckCount > 10){
                    // std::cout << "Server not responding" << std::endl;
                    newNoAcks.clear();
                    // break;
                }else {
                    // std::cout << "no ack -> push back, " << noAcks[i] << std::endl;
                    newNoAcks.push_back(noAcks[i]);
                }
            }else {
                if(ptr->seq != noAcks[i]){
                    // std::cout << "no ack -> seq error, " << noAcks[i] << ", " << ptr->seq << std::endl;
                    newNoAcks.push_back(noAcks[i]);
                }
                noAckCount = 0;
            }
        }
        // std::cout << "newNoAcks size: " << newNoAcks.size() << std::endl;
        if(noAcks.size() == newNoAcks.size()) count++;
        noAcks = newNoAcks;
        if(count > 10) break;
    }
    // std::cout << "Client send end" << std::endl;
}