


#include "coding.hpp"
#include <unistd.h>
#include <fstream>


int main(int argc, char** argv){
    std::string out = encode(argv[1]);
    std::string in = decode(out);
    std::cout << in << std::endl;
    return 0;   
}