#include "tools.hpp"

std::map<uint8_t, uint8_t> map_type_to_size = {
    {INT8_T, 8},
    {UINT8_T, 8},
    {CHAR, 8},
    {BOOL, 8},
    {INT16_T, 16},
    {UINT16_T, 16},
    {INT32_T, 32},
    {UINT32_T, 32},
    {FLOAT, 32},
    {INT64_T, 64},
    {UINT64_T, 64},
    {DOUBLE, 64}
};


uint8_t get_size(uint8_t type){
    return map_type_to_size[type];
}