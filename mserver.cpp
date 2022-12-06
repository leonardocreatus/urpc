#include "rpc_server.hpp"
// #include <semaphore>

Request sum(Request req){
    // std::cout << "req: " << req.str.size() << std::endl;
    Request res(req.str);
    return res;
}

int main(int argc, char** argv){

    if(argc != 6){
        std::cout << "Usage: ./server <ip> <timeout> <windows> <datagram> <coding>" << std::endl;
        return 0;
    }
    
    std::string ip = argv[1];
    int timeout = atoi(argv[2]);
    int windows = atoi(argv[3]);
    int datagram = atoi(argv[4]);
    bool coding = atoi(argv[5]);

    std::cout << "coding: " << coding << std::endl;

    omp_set_num_threads(windows);

    RpcServer rpc(ip, 3000, datagram, timeout, windows, coding);
    rpc.registerFn(15, (void*)sum);
    getchar();
   
}