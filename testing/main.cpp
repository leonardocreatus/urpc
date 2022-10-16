// bitset operators
#include <iostream>       // std::cout
#include <string>         // std::string
#include <bitset>         // std::bitset
#include <any> 
#include <map>


std::map<uint8_t, void*> map_type_to_serialize;

int sum(int a){
    return a + 1;
}




int main ()
{


    // std::function<std::any(std::any)> func = sum;
    // map_type_to_serialize[15] = func;
    // printf("%p", sum);
    map_type_to_serialize[15] = (void*)sum;
    std::function<int(int)> func = (int(*)(int))map_type_to_serialize[15];
    int res = func(5);
    std::cout << res << std::endl;
    // std::any a = sum;
    // std::cout << std::any_cast<int(*)(int)>(a)(1) << std::endl;

    return 0;
}