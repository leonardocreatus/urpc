#include "server.hpp"

Server::Server(int port, std::function<void(std::string)> callback, int payload_size){
    omp_set_num_threads(16);
    int num_threads = omp_get_max_threads();
    
    this->callback = callback;
    this->payload_size = payload_size;
    this->port = port;

    if ((this->s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
        // std::cout << "socket error" << std::endl;
        exit(1);
    }
    memset((char *) &si_me, 0, sizeof(si_me));

    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(port);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(s, (struct sockaddr*)&si_me, sizeof(si_me)) == -1){
        // std::cout << "bind error" << std::endl;
        exit(1);
    }
    this->thread_socket_start = new std::thread(&Server::socket_start, this);
}

Server::~Server(){
    // std::cout << "Server destructor" << std::endl;
    close(s);
    
    this->thread_socket_start->join();
    this->thread_socket_ack->join();
    delete this->thread_socket_ack;
    delete this->thread_socket_start;
    
}

void Server::socket_ack(struct data_s *ptr, socklen_t len){
    // std::cout << "Server socket_ack start" << std::endl;
    char *buf = (char *)ptr;
    if (sendto(s, buf, sizeof(struct data_s), 0 , (struct sockaddr *) &si_other, len) == -1){
        // exit(1);
    }
}

void Server::socket_start(){
    static int last_tid = -1;
    char buf[sizeof(struct data_s) + this->payload_size];
    struct data_s *ptr = (struct data_s *) buf;
    char* data = (char*)buf + sizeof(struct data_s);
    socklen_t len = sizeof(si_other);
    std::map<int, bool> rcvMap;


    // std::cout << "payload_size: " << this->payload_size << std::endl;

    try {
        while(1){
            memset(buf, 0, sizeof(buf));
            if ((recv_len = recvfrom(s, buf, sizeof(struct data_s) + this->payload_size, 0, (struct sockaddr *) &si_other, &len)) == -1){
                std::cout << "recvfrom error!" << std::endl;
                // std::this_thread::sleep_for(std::chrono::milliseconds(200));
                // break;
                continue;
            }


            char* msg = tidToMsg[std::to_string(ptr->tid)];
            int count = tidToCount[std::to_string(ptr->tid)];
            // std::cout << "receive: " << ptr->seq << std::endl;
        
            if(msg == NULL){

                if(last_tid != ptr->tid){
                    // std::cout << "new tid: " << ptr->tid << std::endl;
                    msg = (char*)malloc(ptr->parts * this->payload_size);
                    count = 0;
                    // count = new int(0);
                }else {
                    // std::cout << "msg != NULL" << std::endl;
                    // std::thread(&Server::socket_ack, this, ptr, len).detach();
                    this->socket_ack(ptr, len);
                    continue;     
                }
            }

            if((recv_len - sizeof(struct data_s)) != this->payload_size){
                tidToLetherSize[std::to_string(ptr->tid)] = recv_len - sizeof(struct data_s);
            }

            memcpy(msg + ptr->seq * this->payload_size, data, recv_len - sizeof(struct data_s));
            // std::cout <<  "tid: " << ptr->tid << " seq: " << ptr->seq << " parts: " << ptr->parts << std::endl;
            this->socket_ack(ptr, len);
            // this->thread_socket_ack = new std::thread(&Server::socket_ack, this, ptr, len);


            if(rcvMap[ptr->seq] != true){
                rcvMap[ptr->seq] = true;
                count += 1;
                // std::cout << "count: " << count << std::endl;
            }
            
            if(count == ptr->parts){
                // std::cout << "receive complete" << std::endl;
                last_tid = ptr->tid;
                std::string ss(msg, ((count - 1) * this->payload_size) + tidToLetherSize[std::to_string(ptr->tid)]);

                free(msg);
                // delete count;
                count = 0;

                rcvMap.clear();
                
                tidToMsg.erase(std::to_string(ptr->tid));
                tidToCount.erase(std::to_string(ptr->tid));
                tidToLetherSize.erase(std::to_string(ptr->tid));

                tidToMsg[std::to_string(ptr->tid)] = NULL;
                tidToCount[std::to_string(ptr->tid)] = 0;

                this->callback(ss);
            }else {
                tidToMsg[std::to_string(ptr->tid)] = msg;
            }
            tidToCount[std::to_string(ptr->tid)] = count;
        }
    }catch (const std::overflow_error& e){
        // std::cout << "overflow_error: " << e.what() << std::endl;
    } // this executes if f() throws std::overflow_error (same type rule)
    catch (const std::runtime_error& e){
        // std::cout << "runtime_error: " << e.what() << std::endl;
    } // this executes if f() throws std::runtime_error (base class rule)
    catch (const std::exception& e){
        // std::cout << "exception: " << e.what() << std::endl;
    } // this executes if f() throws std::exception (base class rule)
    catch (...){
        // std::cout << "default exception" << std::endl;
    } // this executes if f() throws anything else

}