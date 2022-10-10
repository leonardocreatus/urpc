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

    Client client(port_client, "127.0.0.1");

    Server server(port_server, [&client, port_client](std::string msg) -> void {
        Request req;
        req.deserialize(msg);
        Response res(req.a + req.b);
        client.send(res.serialize());
    });

    getchar();
}