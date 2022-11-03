#include "rpc_server.hpp"
// #include <semaphore>

Request sum(Request req){
    // std::cout << "req: " << req.str.size() << std::endl;
    Request res(req.str);
    return res;
}

int main(int argc, char** argv){

    if(argc != 5){
        std::cout << "Usage: ./server <ip> <timeout> <windows> <datagram>" << std::endl;
        return 0;
    }
    
    std::string ip = argv[1];
    int timeout = atoi(argv[2]);
    int windows = atoi(argv[3]);
    int datagram = atoi(argv[4]);
    omp_set_num_threads(windows);

    RpcServer rpc(ip, 3000, datagram, timeout, windows);
    rpc.registerFn(15, (void*)sum);
    getchar();
   
}