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

Client client(3001, "127.0.0.1");

std::map<uint8_t, std::function<std::string (std::string msg)>> map_func;

std::string sum(std::string msg){
    Request req;
    req.deserialize(msg);
    uint64_t sum = 0;
    for(auto i : req.vec){
        sum += i;
    }

    Response res(sum);
    return res.serialize();
}


int main(int argc, char** argv){
    
    map_func[15] = sum;

    Server server(3000, [](std::string msg) -> void {
        Request req;
        uint8_t c = msg[0];
        msg = msg.substr(1, msg.length() - 1);
        std::function<std::string(std::string)> callback = map_func[c];
        std::string res = callback(msg);
        client.send((char)c + res);
    });

    getchar();
}