#include "server.hpp"

Server::Server(int port, std::function<void(std::string str, int size)> cb){
    sock = socket(PF_INET6, SOCK_DGRAM, 0);

    if (sock < 0) {
        perror("creating socket");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin6_family = AF_INET6;
    server_addr.sin6_addr = in6addr_any;

    server_addr.sin6_port = htons(port);

    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        exit(2);
    }

    std::thread(&Server::reply, this, cb).detach();
}

void Server::reply(std::function<void(std::string str, int size)> cb){
    while(true){
        clilen = sizeof(client_addr);
        memset(buffer, 0, sizeof(buffer));
        int n = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &clilen);
        if (n < 0) {
            perror("recvfrom failed");
            exit(3);
        }
        std::string str(buffer, n);
        cb(str, n);
    }
}