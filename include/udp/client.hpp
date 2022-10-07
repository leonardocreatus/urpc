#ifndef Client_hpp
#define Client_hpp

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <thread>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <vector>

class Client {
    private: 
        int sock;
        socklen_t clilen;
        struct sockaddr_in server_addr, client_addr;
        char buffer[1024] = { 0 };
        char addrbuf[INET6_ADDRSTRLEN];

    public: 
        Client();
        void request(std::string str, std::string server, int port);
        
};

#endif