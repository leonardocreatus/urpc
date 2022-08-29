#include "unserialize.hpp"

std::map<uint8_t, std::function<void(std::string& str, void*)>> map_type_to_unserialize = {
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
    {DOUBLE, unserialize_double},
    {STRING, unserialize_string}
};

std::function<void(std::string& str, void*)> get_unserialize_func(uint8_t type){
    return map_type_to_unserialize[type];
}


void unserialize_int8_t(std::string& str, void* ptr){
    std::bitset<8> bitset_aux(str.substr(0, 8));
    bool is_negative = str[0] == '1';

    std::bitset<8> twos_comp = std::bitset<8>(bitset_aux.flip().to_ulong() + 1);
    uint32_t value_is_int8_t_unsigned = static_cast<uint32_t>(twos_comp.to_ulong());
    int8_t value_is_int8_t = -static_cast<int8_t>(value_is_int8_t_unsigned);
    *(int8_t*)ptr = value_is_int8_t;
    str = str.substr(8, str.size()); 
}

void unserialize_uint8_t(std::string& str, void* ptr){
    std::bitset<8> bitset_aux(str.substr(0, 8));
    uint8_t value = static_cast<uint8_t>(bitset_aux.to_ulong());
    *(uint8_t*)ptr = value;
    str = str.substr(8, str.size());
}

void unserialize_char(std::string& str, void* ptr){
    std::bitset<8> bitset_aux(str.substr(0, 8));
    char value = static_cast<char>(bitset_aux.to_ulong());
    *(char*)ptr = value;
    str = str.substr(8, str.size());
}

void unserialize_bool(std::string& str, void* ptr){
    std::bitset<8> bitset_aux(str.substr(0, 8));
    bool value = static_cast<bool>(bitset_aux.to_ulong());
    *(bool*)ptr = value;
    str = str.substr(8, str.size());
}

void unserialize_int16_t(std::string& str, void* ptr){
    std::bitset<16> bitset_aux(str.substr(0, 16));
    bool is_negative = str[0] == '1';
    std::bitset<16> twos_comp = std::bitset<16>(bitset_aux.flip().to_ulong() + 1);
    uint32_t value_is_int16_t_unsigned = static_cast<uint32_t>(twos_comp.to_ulong());
    int16_t value_is_int16_t = -static_cast<int16_t>(value_is_int16_t_unsigned);
    *(int16_t*)ptr = value_is_int16_t;
    str = str.substr(16, str.size());
}

void unserialize_uint16_t(std::string& str, void* ptr){
    std::bitset<16> bitset_aux(str.substr(0, 16));
    uint16_t value = static_cast<uint16_t>(bitset_aux.to_ulong());
    *(uint16_t*)ptr = value;
    str = str.substr(16, str.size());
}

void unserialize_int32_t(std::string& str, void* ptr){
    std::bitset<32> bitset_aux(str.substr(0, 32));
    bool is_negative = str[0] == '1';
    std::bitset<32> twos_comp = std::bitset<32>(bitset_aux.flip().to_ulong() + 1);
    uint32_t value_is_int32_t_unsigned = static_cast<uint32_t>(twos_comp.to_ulong());
    int32_t value_is_int32_t = -static_cast<int32_t>(value_is_int32_t_unsigned);
    *(int32_t*)ptr = value_is_int32_t;
    str = str.substr(32, str.size());
}

void unserialize_uint32_t(std::string& str, void* ptr){
    std::bitset<32> bitset_aux(str.substr(0, 32));
    uint32_t value = static_cast<uint32_t>(bitset_aux.to_ulong());
    *(uint32_t*)ptr = value;
    str = str.substr(32, str.size());
}

void unserialize_float(std::string& str, void* ptr){
    std::bitset<32> bitset_aux(str.substr(0, 32));
    union {
        float _float;
        uint32_t _int;
    } data;

    data._int = static_cast<uint32_t>(bitset_aux.to_ulong());;
    *(float*)ptr = data._float;
    str = str.substr(32, str.size());
}

void unserialize_int64_t(std::string& str, void* ptr){
    std::bitset<64> bitset_aux(str.substr(0, 64));
    bool is_negative = str[0] == '1';
    std::bitset<64> twos_comp = std::bitset<64>(bitset_aux.flip().to_ulong() + 1);
    uint64_t value_is_int64_t_unsigned = static_cast<uint64_t>(twos_comp.to_ulong());
    int64_t value_is_int64_t = -static_cast<int64_t>(value_is_int64_t_unsigned);
    *(int64_t*)ptr = value_is_int64_t;
    str = str.substr(64, str.size());
}

void unserialize_uint64_t(std::string& str, void* ptr){
    std::bitset<64> bitset_aux(str.substr(0, 64));
    uint64_t value = static_cast<uint64_t>(bitset_aux.to_ulong());
    *(uint64_t*)ptr = value;
    str = str.substr(64, str.size());
}

void unserialize_double(std::string& str, void* ptr){
    std::bitset<64> bitset_aux(str.substr(0, 64));
    union {
        double _double;
        uint64_t _int;
    } data;

    data._int = static_cast<uint64_t>(bitset_aux.to_ulong());;
    *(double*)ptr = data._double;
    str = str.substr(64, str.size());
}


void unserialize_array(std::string& str, void* ptr, uint8_t type) {
    std::string size_ss = str.substr(0, 32);
    
    uint32_t size = 0;
    unserialize_uint32_t(size_ss, &size);
    uint8_t size_of_type = get_size(type);
    std::string data_ss = str.substr(32, size * size_of_type);

    std::function<void(std::string& str, void*)> func = get_unserialize_func(type);

    for(int i = 0; i < size; i++){
        void* ptr_aux = (void*)((uint8_t*)ptr + i * (size_of_type / 8));
        func(data_ss, ptr_aux);
    }

    if(type == CHAR){
        ((char*)ptr)[size] = '\0';
    }

    str = str.substr(size * size_of_type + 32, str.size());
}

void unserialize_string(std::string& str, void* ptr){
    std::string size_ss = str.substr(0, 32);
    uint32_t size = 0;
    unserialize_uint32_t(size_ss, &size);
    char _ss[size + 1];
    unserialize_array(str, _ss, CHAR);
    std::string* ss = (std::string*)ptr;
    ss->assign(_ss);
}

void unserialize_struct(std::string& serialized, struct metadatas* metadata) {
    for(auto fields : metadata->key_fields) {
        uint8_t type = metadata->type_fields[fields];
        void* ptr = metadata->ptr_fields[fields];
        if(type == STRUCT){
            unserialize_struct(serialized, (struct metadatas*)ptr);
        }else {
            std::function<void(std::string& str, void*)> func = get_unserialize_func(type);
            func(serialized, ptr);
        }
    }
}