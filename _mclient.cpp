#include <string>
#include <iostream>
#include <map>
#include <typeinfo>
#include <iterator>
#include <array>
#include <any>
#include <vector>
#include <any>

#include "include/udp/server/server.hpp"
#include "include/udp/client/client.hpp"

#include "request.hpp"

std::map<uint8_t, void*> map_func;
Client client(3000, "127.0.0.1");

void stub(std::string ss, uint8_t fn_id){
    switch (fn_id){
        case 15: {
            void* fn_void = map_func[fn_id];
            void (*fn)(Request) = (void(*)(Request))fn_void;
            Request req;
            req.deserialize(ss);
            fn(req);
        }; break;
    } 
}

void call(Request req){
    std::cout << "req: " << req.str << std::endl;
}

void sum(Request req, void* callback){ 
    map_func[15] = callback;
    std::string msg = char(15) + req.serialize();
    client.send(msg);
}

int main(int argc, char** argv){
        
    Server server(3001, [](std::string msg) -> void {;
        uint8_t c = msg[0];
        msg = msg.substr(1, msg.length() - 1);
        stub(msg, c);
    });
    
    Request req("ABCDef");

    sum(req, (void*)call);

    getchar();
}