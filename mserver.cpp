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
#include "file.hpp"

Client client(3001, "127.0.0.1");

std::map<uint8_t, std::function<std::string (std::string msg)>> map_func;

std::string sum(std::string msg){
    Request req;
    req.deserialize(msg);
    std::cout << "SUM SERVER" << std::endl;
    return req.serialize();
}



std::string printfilename(std::string msg){
    File file;
    file.deserialize(msg);
    file.name += ".copy";
    std::string serialize = file.serialize();
    return serialize;
}

int main(int argc, char** argv){
    
    map_func[15] = sum;
    map_func[16] = printfilename;

    Server server(3000, [](std::string msg) -> void {
        for(auto i : msg){
            std::cout << (int)i << " ";
        }
        std::cout << std::endl;
        Request req;
        uint8_t c = msg[0];
        msg = msg.substr(1, msg.length() - 1);
        std::cout << "msg size: " << msg.size() << std::endl;
        std::function<std::string(std::string)> callback = map_func[c];
        std::string res = callback(msg);
        std::cout << "res size: " << res.size() << std::endl;
        std::string msgres = char(c) + res;
        client.send(msgres);
    });

    getchar();
}