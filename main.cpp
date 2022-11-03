#include <stdlib.h>
#include <thread>
#include <iostream>
#include <fstream>


void execServer(int datagram){
    std::string cmd = "./server " + std::to_string(datagram);
    system(cmd.c_str());
}


int main(int argc, char** argv){

    
    std::thread(execServer, 4096).detach();

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    int status = std::system("./client 4096 2097152 >> tmp.out");

    std::cout << "Status: " << status << std::endl;
    // if(status == 0){
    //     std::ifstream fs("tmp.out");
    //     std::string str;
    //     std::getline(fs, str);
    //     long int time = std::stol(str);
    //     std::cout << "Time: " << time << std::endl;
    //     fs.close();
    // }

    // remove("tmp.out");
}