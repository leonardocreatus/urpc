#include "./server/server.hpp"
#include "./client/client.hpp"

#include <fstream>

void callback(std::string msg){
    std::cout << msg.size() << std::endl;
    // std::fstream file;
    // file.open("out.jpg", std::ios::out | std::ios::trunc | std::ios_base::binary);
    // file << msg;
    // file.close();
}

int main(int argc, char** argv){
    
    std::cout << argv[1] << std::endl;
    if(strcmp(argv[1], "server") == 0){
        Server server(8888, callback, 16);
        getchar();
    }else {
        Client client(8888, "192.168.64.10", 1, 1, 16);
        std::string msg;
        int size = atoi(argv[2]);
        std::cout << "size: " << size << std::endl;
        for(int i = 0; i < size; i++){
            msg += "a";
        }
        client.send(msg);

        // std::fstream file;
        // file.open("in.jpg", std::ios::in | std::ios_base::binary);
        // if(!file.is_open()){ 
        //     std::cout << "file not open" << std::endl;
        //     exit(1);
        // }
        // std::string msg((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        // client.send(msg);
        // file.close();
    }
}