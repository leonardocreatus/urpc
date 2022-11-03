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
#include "include/arithmetic_coding/coding.hpp"
#include "request.hpp"
// #include <semaphore>



class RpcServer {
    private:


        Server *server;
        Client *client;
        std::map<uint8_t, void*> mapFn;
        // std::counting_semaphore<1>* sem;

        void rcvMsg(std::string msg){
            // std::cout << "rcvMsg msg size: " << msg.size() << std::endl;
            uint8_t c = msg[0];
            msg = msg.substr(1, msg.length() - 1);
            std::string res = stub(msg, c); 
            std::string msgres = char(c) + res;   
            this->client->send(msgres);
            // this->sem->release();
        }

        std::string stub(std::string str, uint8_t fn_id){
            std::string ssres;
            switch (fn_id){
                case 15: {
                    std::function<Request(Request)> fn = (Request(*)(Request))mapFn[fn_id];
                    Request req;
                    // str = decode(str);
                    // printf("pointer req.str.size(): %p\n", req.str);
                    // std::cout << "stub case 15" << &req.str << std::endl;
                    req.deserialize(str);
                    // std::cout << "deserialized" << std::endl;
                    // std::cout << "deserialized !!!!" << std::endl;
                    // std::cout << "req.str.size(): " << req.str.size() << std::endl;
                    // printf("pointer req.str.size(): %p\n", req.str);
                    // std::cout << "stub case 15" << &req.str << std::endl;
                    Request res = fn(req);
                    // std::cout << "res.str.size(): " << res.str.size() << std::endl;
                    // std::cout << "fn end" << std::endl;
                    ssres = res.serialize();
                    // ssres = encode(ssres);
                }; break;
            } 
            // std::cout << "stub end: " << ssres.size() << std::endl;
            return ssres;
        }

    public:
    
        RpcServer(std::string ip, int port, int payload_size, int timeout, int windows) {
            // std::cout << "payload_size: " << payload_size << std::endl;
            // this->sem = new std::counting_semaphore<1>(0);
            this->client = new Client(3001, ip, payload_size, timeout, windows);
            std::function<void(std::string)> fn = std::bind(&RpcServer::rcvMsg, this, std::placeholders::_1);
            this->server = new Server(port, fn, payload_size);
        }

        ~RpcServer(){
            delete this->server;
            delete this->client;
            // delete this->sem;
        }
        
        void registerFn(uint8_t id, void* fn){
            this->mapFn[id] = fn;
            // this->sem->acquire();
        }
};