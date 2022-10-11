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

std::map<uint8_t, std::function<void(std::string)>> map_func;
Client client(3000, "127.0.0.1");

void sum(Request req, std::function<void(std::string res)> callback){
    uint8_t value = 15;
    map_func[value] = callback;
    std::string msg = char(value) + req.serialize();
    std::cout << "size: " << msg.length() << std::endl;
    client.send(msg);
}


int main(int argc, char** argv){
        
    Server server(3001, [](std::string msg) -> void {
        Response res;
        uint8_t c = msg[0];
        msg = msg.substr(1, msg.length() - 1);

        std::function<void(std::string)> callback = map_func[c];
        callback(msg);
    });


    while(true){
        int a, b;
        std::cin >> a >> b;
        std::vector<uint8_t> vec;
        vec.push_back(a);
        vec.push_back(b);
        Request req(vec);

        sum(req, [](std::string ssres) -> void {
            Response res;
            res.deserialize(ssres);
            std::cout << res.x << std::endl;
        });
    }
}