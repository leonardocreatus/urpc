#include <string>
#include <iostream>
#include <map>
#include <typeinfo>
#include <iterator>
#include <array>
#include <any>
#include <vector>

#include "include/udp/server/server.hpp"
#include "include/udp/client/client.hpp"

#include "request.hpp"
#include "response.hpp"

int main(int argc, char** argv){
    
    int port_server = atoi(argv[1]);
    int port_client = atoi(argv[2]);

    // Client client;

    // Server server(port_server, [&client, port_client](std::string ss, int size) -> void {
    //     Response res;
    //     res.deserialize(ss);
    //     std::cout << "Response: " << res.x << std::endl;
    // });

    // getchar();

    // Request r1(1, 2);
    // client.request(r1.serialize(), "127.0.0.1", port_client);

    Client client(port_client, "127.0.0.1");

    Server server(port_server, [&client, port_client](std::string msg) -> void {
        Response res;
        res.deserialize(msg);
        std::cout << "Response: " << res.x << std::endl;
    });

    getchar();

    Request r1(1, 2);
    client.send(r1.serialize()); 

    getchar();
}