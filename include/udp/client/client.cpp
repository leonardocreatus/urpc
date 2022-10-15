#include "client.hpp"

Client::Client(int port, std::string ip, int payload_size, int timeout, int window){
    this->port = port;
    this->ip = ip;
    this->payload_size = payload_size;
    this->timeout = timeout;
    this->window = window;

    if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) exit(1);
    memset((char *) &si_other, 0, sizeof(si_other));
	
    si_other.sin_family = AF_INET;
	si_other.sin_port = htons(this->port);   

    if (inet_aton(this->ip.c_str() , &si_other.sin_addr) == 0) exit(1);
}

void Client::send(std::string msg){
    int parts = ceil(msg.length() / (double)this->payload_size);
    std::vector<int> noAcks;
    int random = rand();
    for(int send = 0; send < parts; send += this->window){
        #pragma omp parallel for
        for(int i = 0 ; i < this->window; i++){
            if(send + i >= parts) break;

            std::string payload = msg.substr((send + i) * this->payload_size, std::min(this->payload_size, (int)msg.length() - ((send + i) * this->payload_size)));
            char buf[sizeof(struct data_s) + this->payload_size];
            struct data_s *ptr = (struct data_s *)buf;
            
            ptr->parts = parts;
            ptr->seq = i + send;
            ptr->tid = random;

            char *data = (char *)buf + sizeof(struct data_s);
            memcpy(data, payload.data(), payload.length());
            if (sendto(s, buf, sizeof(struct data_s) + payload.size() , 0 , (struct sockaddr *) &si_other, slen) == -1) exit(1);

            struct timeval tv;
            tv.tv_sec = 0;
            tv.tv_usec = this->timeout * 1000; // 10ms
            setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

            int recv_len;
            socklen_t len = sizeof(si_other);
            if ((recv_len = recvfrom(s, buf, sizeof(struct data_s) + this->payload_size, 0, (struct sockaddr *) &si_other, &len)) == -1){
                noAcks.push_back(send + i);
            }
        }
    }

    while(noAcks.size() > 0){
        std::vector<int> newNoAcks;
        #pragma omp parallel for
        for(int i = 0; i < noAcks.size(); i++){
            std::string payload = msg.substr(noAcks[i] * this->payload_size, std::min(this->payload_size, (int)msg.length() - (noAcks[i] * this->payload_size)));
            char buf[sizeof(struct data_s) + this->payload_size];
            struct data_s *ptr = (struct data_s *)buf;
            
            ptr->parts = parts;
            ptr->seq = noAcks[i];
            ptr->tid = 0;

            char *data = (char *)buf + sizeof(struct data_s);
            memcpy(data, payload.data(), payload.length());
            if (sendto(s, buf, sizeof(struct data_s) + payload.size() , 0 , (struct sockaddr *) &si_other, slen) == -1) exit(1);

            struct timeval tv;
            tv.tv_sec = 0;
            tv.tv_usec = this->timeout * 1000; // 10ms
            setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

            int recv_len;
            socklen_t len = sizeof(si_other);
            if ((recv_len = recvfrom(s, buf, sizeof(struct data_s) + this->payload_size, 0, (struct sockaddr *) &si_other, &len)) == -1){
                newNoAcks.push_back(noAcks[i]);
            }
        }
        noAcks = newNoAcks;
    }
    
}