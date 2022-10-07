#ifndef Server_hpp
#define Server_hpp

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include <functional>
#include <iomanip>
#include <thread>

class Server {
    private: 
        int sock;
        socklen_t clilen;
        struct sockaddr_in6 server_addr, client_addr;
        char buffer[1024];
        char addrbuf[INET6_ADDRSTRLEN];

        void reply(std::function<void(std::string str, int size)> cb);
    public: 
        Server(int port, std::function<void(std::string str, int size)> cb);
        
};


#endif