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

class RpcClient {

    private:
        Client *client;
        Server *server;
        std::map<uint8_t, void*> mapFn;

        void rcvMsg(std::string msg){
            uint8_t c = msg[0];
            msg = msg.substr(1, msg.length() - 1);
            stub(msg, c);
        }

        void stub(std::string ss, uint8_t fn_id){
            switch (fn_id){
                case 15: {
                    void* fn_void = this->mapFn[fn_id];
                    void (*fn)(Request) = (void(*)(Request))fn_void;
                    Request req;
                    req.deserialize(ss);
                    fn(req);
                }; break;
            } 
        }

        void registerCallback(uint8_t id, void* fn){
            this->mapFn[id] = fn;
        }

    public: 
        RpcClient(uint16_t port) {
            this->client = new Client(3000, "127.0.0.1");
            std::function<void(std::string)> fn = std::bind(&RpcClient::rcvMsg, this, std::placeholders::_1);
            this->server = new Server(port, fn);
        }   

        void call(uint8_t fn_id, std::string ss){
            std::string msg = char(fn_id) + ss;
            this->client->send(msg);
        }

        void sum(Request req, void* callback){
            uint8_t id = 15; 
            this->registerCallback(id, callback);
            std::string msg = req.serialize();
            this->call(id, msg);
        }
};