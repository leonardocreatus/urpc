#include "rpc_client.hpp"


void sum(Request req){
    std::cout << "sum: " << (int)req.a << " + " << (int)req.b << " = " << (int)(req.a + req.b) << std::endl;
}

int main(int argc, char** argv){
    RpcClient rpc(3001);
    uint8_t a = atoi(argv[1]);
    uint8_t b = atoi(argv[2]);
    Request req(a, b);
    rpc.sum(req, (void*)sum);
    getchar();
}