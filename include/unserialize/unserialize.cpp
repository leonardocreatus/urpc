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
    std::cout << "unserialize_int8_t" << std::endl;
    union {
        int8_t value;
        std::bitset<8> bits = 0;
    } aux;
    aux.value = (int8_t)str[0];
    bool is_negative = aux.bits[0] == 1;

    std::bitset<8> twos_comp = std::bitset<8>(aux.bits.flip().to_ulong() + 1);
    uint8_t value_is_int8_t_unsigned = static_cast<uint8_t>(twos_comp.to_ulong());
    int8_t value_is_int8_t = -static_cast<int8_t>(value_is_int8_t_unsigned);
    *(int8_t*)ptr = value_is_int8_t;
    printf("unserialize_int8_t: %d", value_is_int8_t);
    str = str.substr(8 / 8, str.size()); 
}

void unserialize_uint8_t(std::string& str, void* ptr){
    union {
        std::uint8_t value;
        std::bitset<8> bits = 0;
    } aux;
    
    aux.value = str[0];

    uint8_t value = static_cast<uint8_t>(aux.bits.to_ulong());

    *(uint8_t*)ptr = value;
    str = str.substr(1, str.size());
}

void unserialize_char(std::string& str, void* ptr){
    union {
        char value;
        std::bitset<8> bits = 0;
    } aux;
    
    aux.value = (char)str[0];

    char value = static_cast<char>(aux.bits.to_ulong());
    *(char*)ptr = value;
    str = str.substr(8 / 8, str.size());
}

void unserialize_bool(std::string& str, void* ptr){
    union {
        bool value;
        std::bitset<8> bits = 0;
    } aux;
    
    aux.value = (bool)str[0];
    bool value = static_cast<bool>(aux.bits.to_ulong());
    *(bool*)ptr = value;
    str = str.substr(8 / 8, str.size());
}

void unserialize_int16_t(std::string& str, void* ptr){
    union {
        int16_t value;
        std::bitset<16> bits = 0;
    } aux;

    int size = sizeof(aux.value);
    
    for(int i = 0; i < size; i++){
        aux.bits |= std::bitset<16>(str[i]) << (8 * (1 - i));
    }

    bool is_negative = aux.bits[0] == 1;
    std::bitset<16> twos_comp = std::bitset<16>(aux.bits.flip().to_ulong() + 1);
    uint16_t value_is_int16_t_unsigned = static_cast<uint16_t>(twos_comp.to_ulong());
    int16_t value_is_int16_t = -static_cast<int16_t>(value_is_int16_t_unsigned);
    *(int16_t*)ptr = value_is_int16_t;

    str = str.substr(size, str.size());
}

void unserialize_uint16_t(std::string& str, void* ptr){
    // std::bitset<16> bitset_aux(str.substr(0, 16));
    // uint16_t value = static_cast<uint16_t>(bitset_aux.to_ulong());
    // *(uint16_t*)ptr = value;
    // str = str.substr(16, str.size());
    union {
        uint16_t value;
        std::bitset<16> bits = 0;
    } aux;
    
    // byte_aux.value = str[0] << 24 | str[1] << 16 | str[2] << 8 | str[3];
    int size = sizeof(aux.value);
    
    for(int i = 0; i < size; i++){
        aux.bits |= std::bitset<16>(str[i]) << (8 * (1 - i));
    }
    
    uint16_t value = static_cast<uint16_t>(aux.bits.to_ulong());
    *(uint16_t*)ptr = value;
    str = str.substr(size, str.size());
}

void unserialize_int32_t(std::string& str, void* ptr){
    union {
        int32_t value;
        std::bitset<32> bits = 0;
    } aux;
    
    int size = sizeof(aux.value);
    for(int i = 0; i < size; i++){
        aux.bits |= std::bitset<32>(str[i]) << (8 * ((size - 1) - i));
    }

    bool is_negative = aux.bits[0] == 1;

    std::bitset<32> twos_comp = std::bitset<32>(aux.bits.flip().to_ulong() + 1);
    uint32_t value_is_int32_t_unsigned = static_cast<uint32_t>(twos_comp.to_ulong());
    int32_t value_is_int32_t = -static_cast<int32_t>(value_is_int32_t_unsigned);
    *(int32_t*)ptr = value_is_int32_t;

    str = str.substr(size, str.size());
}

void unserialize_uint32_t(std::string& str, void* ptr){

    union {
        uint32_t value;
        std::bitset<32> bits = 0;
    } aux;
    
    int size = sizeof(aux.value);
    for(int i = 0; i < size; i++){
        aux.bits |= std::bitset<32>(str[i]) << (8 * ((size - 1) - i));
    }
    
    uint32_t value = static_cast<uint32_t>(aux.bits.to_ulong());
    *(uint32_t*)ptr = value;
    str = str.substr(4, str.size());
}

void unserialize_float(std::string& str, void* ptr){
    union {
        float value;
        std::bitset<32> bits = 0;
    } aux;

    int size = sizeof(aux.value);
    for(int i = 0; i < size; i++){
        std::bitset<32> bit;
        bit = (0 << 24 ) | (uint8_t)str[i];
        bit <<= (8 * (4 - 1 - i));
        aux.bits |= bit;
    }

    *(float*)ptr = aux.value;
    str = str.substr(size, str.size());
}

void unserialize_int64_t(std::string& str, void* ptr){
    union {
        int64_t value;
        std::bitset<64> bits = 0;
    } aux;
    
    int size = sizeof(aux.value);
    for(int i = 0; i < size; i++){
        std::bitset<64> bit = 0;
        bit = (uint8_t)str[i];
        bit <<= (8 * (size - 1 - i));
        aux.bits |= bit;
    }

    bool is_negative = aux.bits[0] == 1;

    std::bitset<64> twos_comp = std::bitset<64>(aux.bits.flip().to_ulong() + 1);
    uint64_t value_is_int64_t_unsigned = static_cast<uint64_t>(twos_comp.to_ulong());
    int64_t value_is_int64_t = -static_cast<int64_t>(value_is_int64_t_unsigned);
    *(int64_t*)ptr = value_is_int64_t;

    str = str.substr(size, str.size());
}

void unserialize_uint64_t(std::string& str, void* ptr){
    union {
        uint64_t value;
        std::bitset<64> bits = 0;
    } aux;
    
    int size = sizeof(aux.value);
    for(int i = 0; i < size; i++){
        aux.bits |= std::bitset<64>(str[i]) << (8 * ((size - 1) - i));
    }
    
    uint64_t value = static_cast<uint64_t>(aux.bits.to_ulong());
    *(uint64_t*)ptr = value;
    str = str.substr(size, str.size());
}

void unserialize_double(std::string& str, void* ptr){
    // std::bitset<64> bitset_aux(str.substr(0, 64));
    // union {
    //     double _double;
    //     uint64_t _int;
    // } data;

    // data._int = static_cast<uint64_t>(bitset_aux.to_ulong());;
    // *(double*)ptr = data._double;
    // str = str.substr(64, str.size());
    union {
        double value;
        std::bitset<64> bits = 0;
    } aux;

    int size = sizeof(aux.value);
    for(int i = 0; i < size; i++){
        std::bitset<64> bit = 0;
        bit = (uint8_t)str[i];
        // bit = (0 << 56 ) | (uint8_t)str[i];

        bit <<= (8 * (4 - 1 - i));
        aux.bits |= bit;
    }

    *(double*)ptr = aux.value;
    str = str.substr(size, str.size());
}


void unserialize_array(std::string& str, void* ptr, uint8_t type) {
    std::string size_ss = str.substr(0, 4);
    uint32_t size = 0;
    unserialize_uint32_t(size_ss, &size);
    uint8_t size_of_type = get_size(type);
    std::string data_ss = str.substr(4, size * size_of_type);

    std::function<void(std::string& str, void*)> func = get_unserialize_func(type);
    void* p = ptr;
    std::cout << "unserialize array size: " << size << std::endl;
    std::cout << "unserialize array type: " << (int)type << std::endl;

    std::cout << "unserialize get_size: " << (int)get_size(type) << std::endl;
    if(type != CHAR){
        switch(get_size(type)){
            case 8: {
                std::cout << "unserialize array 8" << std::endl;
                std::vector<uint8_t>* vec = (std::vector<uint8_t>*)ptr;
                vec->resize(size);
                p = vec->data(); 
            }; break;
            case 16: {
                std::vector<uint16_t>* vec = (std::vector<uint16_t>*)ptr;
                vec->resize(size);
                p = vec->data(); 
            }; break;
            case 32: {
                std::vector<uint32_t>* vec = (std::vector<uint32_t>*)ptr;
                vec->resize(size);
                p = vec->data(); 
            }; break;
            case 64: {
                std::vector<uint64_t>* vec = (std::vector<uint64_t>*)ptr;
                vec->resize(size);
                p = vec->data(); 
            }; break;
        }
    }
    
    for(int i = 0; i < size; i++){
        std::cout << "unserialize array for, position " << i  << std::endl;
        void* ptr_aux = (void*)((uint8_t*)p + i * get_size(type) / 8);
        func(data_ss, ptr_aux);
    }
    std::cout << "unserialize array end" << std::endl;

    if(type == CHAR){
        ((char*)p)[size] = '\0';
    }

    str = str.substr(size * (size_of_type / 8) + 4, str.size());
    std::cout << " -- unserialize array end" << std::endl;
}

void unserialize_string(std::string& str, void* ptr){
    std::cout << "unserialize string" << std::endl;
    std::string size_ss = str.substr(0, 32 / 8);
    uint32_t size = 0;
    unserialize_uint32_t(size_ss, &size);
    char _ss[size + 1];
    unserialize_array(str, _ss, CHAR);
    std::string* ss = (std::string*)ptr;
    ss->assign(_ss);
}

void unserialize_struct(std::string& serialized, struct metadatas* metadata) {

    std::cout << "unserialize struct" << std::endl;
    for(int i =0; i < serialized.size(); i++){
        std::bitset<8> byte(serialized[i]);
        std::cout << byte.to_string() << " ";
    }
    std::cout << std::endl;
    for(auto fields : metadata->key_fields) {
        uint8_t type = metadata->type_fields[fields];
        void* ptr = metadata->ptr_fields[fields];
        std::cout << "fields: " << fields << std::endl;
        std::cout << "type: " << (int)type << std::endl;
        if(type == OBJECT){
            unserialize_struct(serialized, (struct metadatas*)ptr);
        } else if(type == STRING){
            unserialize_string(serialized, ptr);
        } else if(type > ARRAY){
            uint8_t type_of_array = type - ARRAY;
            unserialize_array(serialized, ptr, type_of_array);
        }else {
            std::function<void(std::string& str, void*)> func = get_unserialize_func(type);
            func(serialized, ptr);
        }
    }
}