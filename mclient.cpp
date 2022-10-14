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

std::map<uint8_t, std::function<void(std::string)>> map_func;
Client client(3000, "127.0.0.1");

void sum(Request req, std::function<void(std::string res)> callback){
    uint8_t value = 15;
    map_func[value] = callback;
    std::string msg = char(value) + req.serialize();
    for(auto i : msg){
        std::cout << (int)i << " ";
    }
    std::cout << std::endl;
    client.send(msg);
}

void printfilename(File file, std::function<void(std::string res)> callback){
    uint8_t value = 16;
    map_func[value] = callback;
    std::cout << "printfilename" << std::endl;
    std::cout << "file name: " << file.name << std::endl;
    std::string msg = char(value) + file.serialize();
    std::cout << "size msg: " << msg.size() << std::endl;
    client.send(msg);
}



int main(int argc, char** argv){
        
    Server server(3001, [](std::string msg) -> void {;
        std::cout << "RECEIVED: " << msg.size() << std::endl;
        uint8_t c = msg[0];

        msg = msg.substr(1, msg.length() - 1);

        std::function<void(std::string)> callback = map_func[c];
        callback(msg);
    });
    
    std::vector<double> vec = {std::numeric_limits<double>::max(), std::numeric_limits<double>::min()};
    for(auto i : vec){
        std::cout << i << std::endl;
    }
    Request req(vec);

    Request req2;
    req2.deserialize(req.serialize());
    std::cout << "req 2" << std::endl;
    for(auto i : req2.vec){
        std::cout << i << std::endl;
    }
    std::cout << "END" << std::endl;
    sum(req, [](std::string res){
        std::cout << "SUM CLIENT" << std::endl;
        Request r;
        r.deserialize(res);
    
        std::cout << "size: " << r.vec.size() << std::endl;

        for(int i = 0 ; i < r.vec.size() ; i++){
            // std::cout << "i: " << (float)r.vec[i] << std::endl;
            // printf("i: %lld \n", r.vec[i]);
            std::cout << "i: " << r.vec[i] << std::endl;
        }
    });

    getchar();
    // while(true){

    //     int a, b;
    //     std::cin >> a >> b;
    //     std::vector<uint8_t> vec;
    //     vec.push_back(a);
    //     vec.push_back(b);
    //     Request req(vec);

    //     sum(req, [](std::string ssres) -> void {
    //         Response res;
    //         res.deserialize(ssres);
    //         std::cout << res.x << std::endl;
    //     });

        // std::string filename;
        // std::cin >> filename;

        // std::fstream ifs;
        // ifs.open(filename, std::ios::in | std::ios_base::binary);

        // if(!ifs.is_open()){
        //     std::cout << "file not open" << std::endl;
        //     exit(1);
        // }

        // std::string content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
        // std::cout << "content size: " << content.size() << std::endl;

        // File f(filename, content);
        // ifs.close();

        // printfilename(f, [](std::string ssres) -> void {
        //     File f;
        //     f.deserialize(ssres);

        //     printf("newfilename: %s\n", f.name.c_str());
            
        //     std::fstream ofs;
        //     ofs.open(f.name.c_str(), std::ios::out | std::ios::trunc | std::ios_base::binary);
        //     ofs << f.content;
        //     ofs.close();
        // });

    // }
}