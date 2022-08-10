#include "unserialize.hpp"

std::map<uint8_t, std::function<void(std::string str, void*)>> map_type_to_unserialize= {
    {INT8_T, unserialize_int8_t},
    {UINT8_T, unserialize_uint8_t},
    {CHAR, unserialize_char},
    {BOOL, unserialize_bool},
    {INT16_T, unserialize_int16_t},
    {UINT16_T, unserialize_uint16_t},
    {INT32_T, unserialize_int32_t},
    {UINT32_T, unserialize_uint32_t},
    {FLOAT, unserialize_float},
    {INT64_T, unserialize_int64_t},
    {UINT64_T, unserialize_uint64_t},
    {DOUBLE, unserialize_double}
};

std::map<uint8_t, uint8_t> _map_type_to_size = {
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

void unserialize_int8_t(std::string str, void* ptr){
    std::bitset<8> bitset_aux(str);
    bool is_negative = str[0] == '1';
    std::bitset<8> twos_comp = std::bitset<8>(bitset_aux.flip().to_ulong() + 1);
    uint32_t value_is_int8_t_unsigned = static_cast<uint32_t>(twos_comp.to_ulong());
    int8_t value_is_int8_t = -static_cast<int8_t>(value_is_int8_t_unsigned);
    *(int8_t*)ptr = value_is_int8_t;
}

void unserialize_uint8_t(std::string str, void* ptr){
    std::bitset<8> bitset_aux(str);
    uint8_t value = static_cast<uint8_t>(bitset_aux.to_ulong());
    *(uint8_t*)ptr = value;
}

void unserialize_char(std::string str, void* ptr){
    std::bitset<8> bitset_aux(str);
    char value = static_cast<char>(bitset_aux.to_ulong());
    *(char*)ptr = value;
}

void unserialize_bool(std::string str, void* ptr){
    std::bitset<8> bitset_aux(str);
    bool value = static_cast<bool>(bitset_aux.to_ulong());
    *(bool*)ptr = value;
}

void unserialize_int16_t(std::string str, void* ptr){
    std::bitset<16> bitset_aux(str);
    bool is_negative = str[0] == '1';
    std::bitset<16> twos_comp = std::bitset<16>(bitset_aux.flip().to_ulong() + 1);
    uint32_t value_is_int16_t_unsigned = static_cast<uint32_t>(twos_comp.to_ulong());
    int16_t value_is_int16_t = -static_cast<int16_t>(value_is_int16_t_unsigned);
    *(int16_t*)ptr = value_is_int16_t;
}

void unserialize_uint16_t(std::string str, void* ptr){
    std::bitset<16> bitset_aux(str);
    uint16_t value = static_cast<uint16_t>(bitset_aux.to_ulong());
    *(uint16_t*)ptr = value;
}

void unserialize_int32_t(std::string str, void* ptr){
    std::bitset<32> bitset_aux(str);
    bool is_negative = str[0] == '1';
    std::bitset<32> twos_comp = std::bitset<32>(bitset_aux.flip().to_ulong() + 1);
    uint32_t value_is_int32_t_unsigned = static_cast<uint32_t>(twos_comp.to_ulong());
    int32_t value_is_int32_t = -static_cast<int32_t>(value_is_int32_t_unsigned);
    *(int32_t*)ptr = value_is_int32_t;
}

void unserialize_uint32_t(std::string str, void* ptr){
    std::bitset<32> bitset_aux(str);
    uint32_t value = static_cast<uint32_t>(bitset_aux.to_ulong());
    *(uint32_t*)ptr = value;
}

void unserialize_float(std::string str, void* ptr){
    std::bitset<32> bitset_aux(str);
    union {
        float _float;
        uint32_t _int;
    } data;

    data._int = static_cast<uint32_t>(bitset_aux.to_ulong());;
    *(float*)ptr = data._float;
}

void unserialize_int64_t(std::string str, void* ptr){
    std::bitset<64> bitset_aux(str);
    bool is_negative = str[0] == '1';
    std::bitset<64> twos_comp = std::bitset<64>(bitset_aux.flip().to_ulong() + 1);
    uint64_t value_is_int64_t_unsigned = static_cast<uint64_t>(twos_comp.to_ulong());
    int64_t value_is_int64_t = -static_cast<int64_t>(value_is_int64_t_unsigned);
    *(int64_t*)ptr = value_is_int64_t;
}

void unserialize_uint64_t(std::string str, void* ptr){
    std::bitset<64> bitset_aux(str);
    uint64_t value = static_cast<uint64_t>(bitset_aux.to_ulong());
    *(uint64_t*)ptr = value;
}

void unserialize_double(std::string str, void* ptr){
    std::bitset<64> bitset_aux(str);
    union {
        double _double;
        uint64_t _int;
    } data;

    data._int = static_cast<uint64_t>(bitset_aux.to_ulong());;
    *(double*)ptr = data._double;
}


void unserialize_array(std::string str, void* ptr, uint8_t type) {
    std::string size_ss = str.substr(0, 32);
    std::string data_ss = str.substr(32, str.size());
    // std::cout << "str: " << str << std::endl;
    // std::cout << "size_ss: " << size_ss << std::endl;
    // std::cout << "data_ss: " << data_ss << std::endl;

    uint32_t size = 0;
    unserialize_uint32_t(size_ss, &size);

    for(int i = 0; i < size; i++){
        void* ptr_aux = (void*)((uint8_t*)ptr + i * (_map_type_to_size[type] / 8));
        map_type_to_unserialize[type](data_ss.substr(i * _map_type_to_size[type], _map_type_to_size[type]), ptr_aux);
    }

    // int it = 0;
    // while(it < size) {
    //     switch(type) {
    //         case INT8_T:
    //             unserialize_int8_t(data_ss.substr(it * 8, 8), (int8_t*)ptr + it);
    //             break;
    //         case UINT8_T:
    //             unserialize_uint8_t(data_ss.substr(it * 8, 8), (uint8_t*)ptr + it);
    //             break;
    //         case CHAR:
    //             unserialize_char(data_ss.substr(it * 8, 8), (char*)ptr + it);
    //             break;
    //         case BOOL:
    //             unserialize_bool(data_ss.substr(it * 8, 8), (bool*)ptr + it);
    //             break;
    //         case INT16_T:
    //             unserialize_int16_t(data_ss.substr(it * 16, 16), (int16_t*)ptr + it);
    //             break;
    //         case UINT16_T:
    //             unserialize_uint16_t(data_ss.substr(it * 16, 16), (uint16_t*)ptr + it);
    //             break;
    //         case INT32_T:
    //             unserialize_int32_t(data_ss.substr(it * 32, 32), (int32_t*)ptr + it);
    //             break;
    //         case UINT32_T:
    //             unserialize_uint32_t(data_ss.substr(it * 32, 32), (uint32_t*)ptr + it);
    //             break;
    //         case FLOAT:
    //             unserialize_float(data_ss.substr(it * 32, 32), (float*)ptr + it);
    //             break;
    //         case INT64_T:
    //             unserialize_int64_t(data_ss.substr(it * 64, 64), (int64_t*)ptr + it);
    //             break;
    //         case UINT64_T:
    //             unserialize_uint64_t(data_ss.substr(it * 64, 64), (uint64_t*)ptr + it);
    //             break;
    //         case DOUBLE:
    //             unserialize_double(data_ss.substr(it * 64, 64), (double*)ptr + it);
    //             break;
    //     }
    //     it++;
    // }

}