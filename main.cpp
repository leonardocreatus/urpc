#include <serialize/serialize.hpp>
#include <unserialize/unserialize.hpp>
#include <string>
#include <iostream>

int main(int argc, char** agrv){
    // uint8_t array[] = {0,1,2,3,4,5};
    // std::string serialized = serialize_array(array, UINT8_T, 6);
    // uint8_t array2[6];
    // unserialize_array(serialized, array2, UINT8_T);
    // for(int i = 0; i < 6; i++) {
    //     printf("%d\n", array2[i]);
    // }
    
    // std::cout << serialized << std::endl;
    // uint8_t n = 10;
    // std::string str = serialize_uint8_t(&n);
    // n = 11;
    // unserialize_int8_t(str, &n);

    double array[] = {0,1,2,3,4,5};
    std::string serialized = serialize_array(array, DOUBLE, 6);
    std::cout << serialized << std::endl;
    double array2[6];

    unserialize_array(serialized, array2, DOUBLE);
    for(int i = 0; i < 6; i++) {
        printf("%f\n", array2[i]);
    }
    
}                    
