#include "rpc_client.hpp"
#include <chrono>
#include <fstream>
// #include <semaphore>
#include <iostream>
#include <iomanip>
#include <vector>

//   65  704 000
// 1 018 618 000
//   65  091 000

// std::counting_semaphore<1> sem(0);

auto start = std::chrono::high_resolution_clock::now();
std::chrono::system_clock::duration res;

std::map<int, std::vector<std::chrono::system_clock::duration>> map;
int lastSize = 0;

std::string ip;
int timeout;
int windows;
int datagram;
int size;

void callback(Request req);
RpcClient *client;

void fn(){
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::string str;

    for(int i = 0; i < size; i++){
        str += "a";
    }

    
    Request req(str);
    start = std::chrono::high_resolution_clock::now();
    client->sum(req, (void*)callback);
}

void callback(Request req){
    if(lastSize != req.str.size()){
        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::system_clock::duration diff = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
        res = diff;
        printf("%ld", res.count());
        exit(0);
        // std::cout << req.str.size() << " " << res.count();
        // std::cout << res.count();
        

        // if(size < 1024 * 32){
        //     exit(0);
        //     size += 1024;
        //     fn();
        // }else{
        //     exit(0);
        // }

    }
}


int main(int argc, char** argv){
    
    if(argc != 6){
        std::cout << "Usage: ./client <ip> <timeout> <windows> <datagram> <size>" << std::endl;
        return 0;
    }

    ip = argv[1];
    timeout = atoi(argv[2]);
    windows = atoi(argv[3]);
    datagram = atoi(argv[4]);
    size = atoi(argv[5]);

    omp_set_num_threads(windows);

    // 

    try {
        client = new RpcClient(ip, 3001, datagram, timeout, windows);
        fn();
        
        getchar();
    }catch(std::exception e){}

    getchar();
    return 0;
}