


#include "coding.hpp"
#include <unistd.h>
#include <fstream>


int main(int argc, char** argv){
    std::string out = encode(argv[1]);
    std::string in = decode(out);

    std::cout << "out: " << out.length() << std::endl;
    std::cout << "in: " << in.length() << std::endl;
    return 0;   
}