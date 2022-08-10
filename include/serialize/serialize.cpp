#include "serialize.hpp"

std::map<uint8_t, std::function<std::string(void*)>> map_type_to_serialize = {
    {INT8_T, serialize_int8_t},
    {UINT8_T, serialize_uint8_t},
    {CHAR, serialize_char},
    {BOOL, serialize_bool},
    {INT16_T, serialize_int16_t},
    {UINT16_T, serialize_uint16_t},
    {INT32_T, serialize_int32_t},
    {UINT32_T, serialize_uint32_t},
    {FLOAT, serialize_float},
    {INT64_T, serialize_int64_t},
    {UINT64_T, serialize_uint64_t},
    {DOUBLE, serialize_double}
};

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

std::string serialize_int8_t(void* ptr){
    std::bitset<8> bits(*(int8_t*)ptr);
    return bits.to_string();
}

std::string serialize_uint8_t(void* ptr){
    std::bitset<8> bits(*(uint8_t*)ptr);
    return bits.to_string();
}

std::string serialize_char(void* ptr){
    std::bitset<8> bits(*(char*)ptr);
    return bits.to_string();
}

std::string serialize_bool(void* ptr){
    std::bitset<8> bits(*(bool*)ptr);
    return bits.to_string();
}

std::string serialize_int16_t(void* ptr){
    std::bitset<16> bits(*(int16_t*)ptr);
    return bits.to_string();
}

std::string serialize_uint16_t(void* ptr){
    std::bitset<16> bits(*(uint16_t*)ptr);
    return bits.to_string();
}

std::string serialize_int32_t(void* ptr){
    std::bitset<32> bits(*(int32_t*)ptr);
    return bits.to_string();
}

std::string serialize_uint32_t(void* ptr){
    std::bitset<32> bits(*(uint32_t*)ptr);
    return bits.to_string();
}

std::string serialize_float(void* ptr){
    union {
        float _float;
        uint32_t _int;
    } data;
    data._float = *(float*)ptr;
    std::bitset<32> bits(data._int);
    return bits.to_string();
}

std::string serialize_int64_t(void* ptr){
    std::bitset<64> bits(*(int64_t*)ptr);
    return bits.to_string();
}

std::string serialize_uint64_t(void* ptr){
    std::bitset<64> bits(*(uint64_t*)ptr);
    return bits.to_string();
}

std::string serialize_double(void* ptr){
    union {
        double _double;
        uint64_t _int;
    } data;
    data._double = *(double*)ptr;
    std::bitset<64> bits(data._int);
    return bits.to_string();
}

std::string serialize_array(void* ptr, uint8_t type, uint32_t size){
    std::string serialized;
    serialized += serialize_uint32_t(&size);

    for(int i = 0; i < size; i++){
        serialized += map_type_to_serialize[type]((char*)ptr + i * map_type_to_size[type] / 8);
    }
    return serialized;
}