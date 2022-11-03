#ifndef CLIENT_HPP
#define CLIENT_HPP

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
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <omp.h>

#include "../tools/data_s.h"

class Client {
    private:
        struct sockaddr_in si_other;
        int s, i, slen = sizeof(si_other);

        std::string ip;
        int port;
        int payload_size;
        int timeout;
        int window;
    
    public:
        // Client(int port, std::string ip);
        Client(int port, std::string ip, int payload_size = 512, int timeout = 10, int window = 16);
        ~Client();
        void send(std::string msg);
};


#endif