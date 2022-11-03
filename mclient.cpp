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


void callback(Request req){
    // std::cout << "callback" << std::endl;
    // std::cout << "req.str.size: " << req.str.size() << std::endl;
    if(lastSize != req.str.size()){
        // std::cout << "callback point 1" << std::endl;
        auto finish = std::chrono::high_resolution_clock::now();
        // std::cout << "callback point 2" << std::endl;
        std::chrono::system_clock::duration diff = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
        // std::cout << "callback point 3" << std::endl;
        res = diff;
        // std::cout << "callback point 4" << std::endl;
        std::cout << res.count();
        // std::cout << "callback point 5" << std::endl;
        exit(0);
        // sem.release();
    }
}

int main(int argc, char** argv){
    
    if(argc != 6){
        std::cout << "Usage: ./client <ip> <timeout> <windows> <datagram> <size>" << std::endl;
        return 0;
    }

    std::string ip = argv[1];
    int timeout = atoi(argv[2]);
    int windows = atoi(argv[3]);
    int datagram = atoi(argv[4]);
    int size = atoi(argv[5]);
    omp_set_num_threads(windows);

    try {
        RpcClient rpc(ip, 3001, datagram, timeout, windows);
        std::string str;
        for(int i = 0; i < size; i++){
            str += "a";
        }

        Request req(str);
        start = std::chrono::high_resolution_clock::now();
        rpc.sum(req, (void*)callback);
        // sem.acquire()

        getchar();
    
    }catch(std::exception e){
        // std::cout << e.what() << std::endl;
    }

    // std::cout << "result: " << res.count() << std::endl;
    getchar();
    return 0;
}