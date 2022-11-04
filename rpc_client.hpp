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
#include "include/arithmetic_coding/coding.hpp"

#include "request.hpp"



class RpcClient {

    

    private:

        std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
        std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();

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
                    // printf("[%d] stub pointer: %p\n", fn_id, fn_void);
                    // void (*fn)(Request) = (void(*)(Request))fn_void;
                    // std::function<void(Request)> fn = (void(Request))fn_void;
                    //converting void* to function pointer
                    void (*fn)(Request) = (void(*)(Request))fn_void;

                    // ss = decode(ss);
                    Request req;
                    req.deserialize(ss);
                    // std::cout << "stub fn, size: " << req.str.size() << std::endl;
                    // printf("fn pointer: %p\n", fn);
                    // fn(req);
                    // execute function fn
                    fn(req);
                    // std::cout << "stub fn end" << std::endl;
                }; break;
            } 
        }

        void registerCallback(uint8_t id, void* fn){
            this->mapFn[id] = fn;
        }

    public: 
        RpcClient(std::string ip, uint16_t port, int payload_size, int timeout, int windows) {
            this->client = new Client(3000, ip, payload_size, timeout, windows);
            std::function<void(std::string)> fn = std::bind(&RpcClient::rcvMsg, this, std::placeholders::_1);
            this->server = new Server(port, fn, payload_size);
        }

        ~RpcClient(){
            delete this->client;
            delete this->server;
        }

        void call(uint8_t fn_id, std::string ss){
            std::string msg = char(fn_id) + ss;
            // std::cout << "msg call size: " << ss.size() << std::endl;
            this->client->send(msg);
        }

        void sum(Request req, void* callback){
            uint8_t id = 15;
            // printf("[%d] callback pointer: %p\n", id, callback);
            this->registerCallback(id, callback);
            std::string msg = req.serialize();
            // msg = encode(msg);
            this->call(id, msg);
        }
};