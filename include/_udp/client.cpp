#include "client.hpp"

Client::Client(){
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock < 0) {
        perror("creating socket");
        exit(1);
    }
}

void Client::request(std::string str, std::string server, int port){
    memset(&server_addr, 0, sizeof(server));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if (inet_aton(server.c_str(), &server_addr.sin_addr) == 0) {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

    int n = sendto(sock, str.c_str(), str.size(), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (n < 0) {
        perror("sendto failed");
        exit(1);
    }

    // close(sock);
}