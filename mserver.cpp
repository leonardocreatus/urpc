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

Client client(3001, "127.0.0.1");

std::map<uint8_t, void*> map_func;

Request sum(Request req){
    Request res(req.str + "123");
    return res;
}

std::string stumb(std::string str, uint8_t fn_id){
    std::string ssres;
    switch (fn_id){
        case 15: {
            std::function<Request(Request)> func = (Request(*)(Request))map_func[fn_id];
            Request req;
            req.deserialize(str);
            Request res = func(req);
            ssres = res.serialize();
        }; break;
    } 

    return ssres;
}


int main(int argc, char** argv){
    
    map_func[15] = (void*)sum;

    Server server(3000, [](std::string msg) -> void {
        uint8_t c = msg[0];
        msg = msg.substr(1, msg.length() - 1);
        std::string res = stumb(msg, c); 
        std::string msgres = char(c) + res;      
        client.send(msgres);
    });

    getchar();
}