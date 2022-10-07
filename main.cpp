#include <string>
#include <iostream>
#include <map>
#include <typeinfo>
#include <iterator>
#include <array>
#include <any>
#include <vector>

#include "include/udp/server.hpp"
#include "include/udp/client.hpp"
#include "sum.hpp"



void print(std::string str, int size){
    // for(int i = 0; i < size; i++){
    //     printf("%02x\n", str[i]);
    // }
    // std::cout << str << std::endl;
    // printf("serialize size: %d\n", str.size());
    w
int main(int argc, char** argv){

    // std::vector<int32_t> values{1, 2, 3};
    // Sum s1(values);
    // std::string serialize = s1.serialize();

    // Sum s2;
    // s2.deserialize(serialize);
    // for(auto i : s2.values){
    //     std::cout << i << std::endl;
    // }

    int port_server = atoi(argv[1]);
    int port_client = atoi(argv[2]);

    
    Client client;

    Server server(port_server, [&client, port_client](std::string ss, int size) -> void{
        // std::cout << "server: " << size << std::endl;
        Sum s;
        s.deserialize(ss);
        int32_t sum = 0;
        for(auto i : s.values){
            sum += i;
        }
        std::cout << "sum: " << sum << std::endl;
        s.values.clear();
        if(size > 8){
            s.values.push_back(sum);
            client.request(s.serialize(), "127.0.0.1", port_client);
        }
    });

    while(true){
        std::cout << "Insira valores para somar ou 0 para sair e executar a soma remotamente ... " << std::endl;
        std::vector<int32_t> values;
        while(true){
    
            int value;
            std::cin >> value;
            if(value == 0){
                break;
            }
            values.push_back(value);
        }
        Sum s1(values);
        std::string serialize = s1.serialize();
        client.request(serialize, "127.0.0.1", port_client);
    }

}                    