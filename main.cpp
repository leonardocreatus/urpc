#include <serialize/serialize.hpp>
#include <unserialize/unserialize.hpp>
#include <string>
#include <iostream>

int main(int argc, char** agrv){

    std::string ss = "batata";
    std::string serialized = serialize_string(&ss);
    std::cout << serialized << std::endl;
    std::string ss2;
    unserialize_string(serialized, &ss2);
    std::cout << ss2 << std::endl;
    
}                    
