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

class RpcServer {
    private:
        Server *server;
        Client *client;
        std::map<uint8_t, void*> mapFn;

        void rcvMsg(std::string msg){
            uint8_t c = msg[0];
            msg = msg.substr(1, msg.length() - 1);
            std::string res = stub(msg, c); 
            std::string msgres = char(c) + res;      
            this->client->send(msgres);
        }

        std::string stub(std::string str, uint8_t fn_id){
            std::string ssres;
            switch (fn_id){
                case 15: {
                    std::function<Request(Request)> fn = (Request(*)(Request))mapFn[fn_id];
                    Request req;
                    req.deserialize(str);
                    Request res = fn(req);
                    ssres = res.serialize();
                }; break;
            } 
            return ssres;
        }

    public:
    
        RpcServer(int port){
            this->client = new Client(3001, "127.0.0.1");
            std::function<void(std::string)> fn = std::bind(&RpcServer::rcvMsg, this, std::placeholders::_1);
            this->server = new Server(port, fn);
        }
        
        void registerFn(uint8_t id, void* fn){
            this->mapFn[id] = fn;
        }
};