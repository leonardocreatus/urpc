#ifndef SERVER_HPP
#define SERVER_HPP

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <vector>
#include <utility>
#include <thread>
#include <chrono>
#include <functional>
#include <map>
#include <stdlib.h>
#include <algorithm>
#include <fstream>
#include <omp.h>

#include "../tools/data_s.h"


class Server {
    private: 
        struct sockaddr_in si_me, si_other;
        int s, i, slen = sizeof(si_other) , recv_len;
        std::function<void(std::string)> callback;
        std::map<std::string, char*> tidToMsg;
        std::map<std::string, int> tidToCount;
        std::map<std::string, int> tidToLetherSize;
        std::thread *thread_socket_start;
        std::thread *thread_socket_ack;


        int port;
        int payload_size;

        void socket_start();
        void socket_close();
        void socket_ack(struct data_s *ptr, socklen_t len);
    public:
        Server(int port, std::function<void(std::string)> callback, int payload_size = 512);
        ~Server();
};

#endif

