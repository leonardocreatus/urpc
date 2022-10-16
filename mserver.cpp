#include "rpc_server.hpp"

Request sum(Request req){
    Request res(req.a + req.b, 0);
    return res;
}

int main(int argc, char** argv){

    RpcServer rpc(3000);
    rpc.registerFn(15, (void*)sum);
    
    getchar();
}