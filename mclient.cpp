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
bool coding;
std::string str;

void callback(Request req);
RpcClient *client;

void fn(){
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    // std::string str;
    std::ifstream file("/home/texto.txt");
    // std::cout << "good: " << file.good() << std::endl;
    std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    str = str.substr(0, size);
    // std::cout << "str.size(): " << str.size() << " size: " << size << std::endl;
    file.close();

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
    }
}


int main(int argc, char** argv){
    if(argc != 7){
        std::cout << "Usage: ./client <ip> <timeout> <windows> <datagram> <size> <coding>" << std::endl;
        return 0;
    }

    ip = argv[1];
    timeout = atoi(argv[2]);
    windows = atoi(argv[3]);
    datagram = atoi(argv[4]);
    size = atoi(argv[5]);
    coding = atoi(argv[6]);
    
    omp_set_num_threads(windows);

    try {
        client = new RpcClient(ip, 3001, datagram, timeout, windows, coding);
        fn();
        
        getchar();
    }catch(std::exception e){}

    getchar();
    return 0;
}