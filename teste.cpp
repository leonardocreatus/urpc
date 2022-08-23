#include <iostream>
#include <string>

void batata(std::string &ss){
    ss = ss.substr(1, ss.size());;
}

int main(int argc, char** argv){
    std::string ss = "batata";
    std::cout << ss << std::endl;
    // batata(ss);
    // char* b = &ss;
    char* n;
    strcpy(n, ss.c_str());
    // n[0] = n[1];
    // &n += 1;
    n += 1;
    // b += 8;
    std::cout << n << std::endl;

}