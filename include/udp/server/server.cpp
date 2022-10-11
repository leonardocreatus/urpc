#include "server.hpp"

Server::Server(int port, std::function<void(std::string)> callback, int payload_size){
    this->callback = callback;
    this->payload_size = payload_size;
    this->port = port;

    if ((this->s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) exit(1);
    memset((char *) &si_me, 0, sizeof(si_me));

    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(port);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(s, (struct sockaddr*)&si_me, sizeof(si_me)) == -1) exit(1);
    std::thread(&Server::socket_start, this).detach();

}

void Server::socket_ack(struct data_s *ptr, socklen_t len){
    char *buf = (char *)ptr;
    if (sendto(s, buf, sizeof(struct data_s), 0 , (struct sockaddr *) &si_other, len) == -1) exit(1);
}

void Server::socket_start(){
    char buf[sizeof(struct data_s) + this->payload_size];
    struct data_s *ptr = (struct data_s *) buf;
    char* data = (char*)buf + sizeof(struct data_s);
    socklen_t len = sizeof(si_other);
    while(1){
        memset(buf, 0, sizeof(buf));
        if ((recv_len = recvfrom(s, buf, sizeof(struct data_s) + this->payload_size, 0, (struct sockaddr *) &si_other, &len)) == -1) exit(1);
        char* msg = tidToMsg[std::to_string(ptr->tid)];
        int* count = tidToCount[std::to_string(ptr->tid)];
        if(msg == NULL){
            if(ptr->seq == 0) {
                msg = (char*)malloc(ptr->parts * this->payload_size);
                count = new int(0);
            }else {
                std::thread(&Server::socket_ack, this, ptr, len).detach();
                continue;
            }
        }

        if((recv_len - sizeof(struct data_s)) != this->payload_size){
            tidToLetherSize[std::to_string(ptr->tid)] = recv_len - sizeof(struct data_s);
        }

        memcpy(msg + ptr->seq * this->payload_size, data, recv_len - sizeof(struct data_s));
        std::thread(&Server::socket_ack, this, ptr, len).detach();
        std::cout << "count: " << *count << " parts: " << ptr->parts << std::endl;
        if(++(*count) == ptr->parts){
            std::string ss(msg, ((*count - 1) * this->payload_size) + tidToLetherSize[std::to_string(ptr->tid)]);
            std::cout << ss.size() << std::endl;
            this->callback(ss);
            
            free(msg);
            delete count;
            
            tidToMsg.erase(std::to_string(ptr->tid));
            tidToCount.erase(std::to_string(ptr->tid));
            tidToLetherSize.erase(std::to_string(ptr->tid));

            tidToMsg[std::to_string(ptr->tid)] = NULL;
            tidToCount[std::to_string(ptr->tid)] = NULL;
        }else {
            tidToMsg[std::to_string(ptr->tid)] = msg;
            tidToCount[std::to_string(ptr->tid)] = count;
        }
    }
}