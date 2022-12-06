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
    {DOUBLE, serialize_double},
    {STRING, serialize_string}
};

std::function<std::string(void*)> get_serialize_func(uint8_t type){
    return map_type_to_serialize[type];
}

std::string serialize_int8_t(void* ptr){
    std::bitset<8> bits(*(int8_t*)ptr);

    std::string serialize_parse;
    serialize_parse += bits.to_ulong();
    return serialize_parse;
}

std::string serialize_uint8_t(void* ptr){
    std::bitset<8> bits(*(uint8_t*)ptr);
    // return bits.to_string();

    std::string serialize_parse;
    serialize_parse += bits.to_ulong();
    return serialize_parse;
}

std::string serialize_char(void* ptr){
    std::bitset<8> bits(*(char*)ptr);
    std::string serialize_parse;
    serialize_parse += bits.to_ulong();
    return serialize_parse;

    // int value = *(char*)ptr;
    // std::string serialize_parse;
    // serialize_parse += value;
    // return serialize_parse;
}

std::string serialize_bool(void* ptr)
{
    throw std::runtime_error("Not implemented");
    std::bitset<8> bits(*(bool*)ptr);
    std::string serialize_parse;
    serialize_parse += bits.to_ulong();
    return serialize_parse;
}

std::string serialize_int16_t(void* ptr){
    std::bitset<16> bits(*(int16_t*)ptr);
    // return bits.to_string();

    std::string serialize_parse;
    uint16_t value = bits.to_ulong();
    serialize_parse += (value >> 8);
    serialize_parse += (value >> 0);
    return serialize_parse;
}

std::string serialize_uint16_t(void* ptr){
    std::bitset<16> bits(*(uint16_t*)ptr);
    std::string serialize_parse;
    uint16_t value = bits.to_ulong();
    serialize_parse += (value >> 8);
    serialize_parse += (value >> 0);
    return serialize_parse;
}

std::string serialize_int32_t(void* ptr){
    std::bitset<32> bits(*(int32_t*)ptr);
    std::string serialize_parse;
    uint32_t value = bits.to_ulong();
    serialize_parse += (value >> 24);
    serialize_parse += (value >> 16);
    serialize_parse += (value >> 8);
    serialize_parse += (value >> 0);

    return serialize_parse;
}

std::string serialize_uint32_t(void* ptr){
    std::bitset<32> bits(*(uint32_t*)ptr);
    std::string serialize_parse;
    uint32_t value = bits.to_ullong();
    serialize_parse += (value >> 24);
    serialize_parse += (value >> 16);
    serialize_parse += (value >> 8);
    serialize_parse += (value >> 0);
    return serialize_parse;
}

std::string serialize_float(void* ptr){
    union {
        float _float;
        uint32_t _int;
    } data;
    data._float = *(float*)ptr;
    std::bitset<32> bits(data._int);

    std::string serialize_parse;
    uint32_t value = bits.to_ulong();

    serialize_parse += (value >> 24);
    serialize_parse += (value >> 16);
    serialize_parse += (value >> 8);
    serialize_parse += (value >> 0);

    return serialize_parse;
}

std::string serialize_int64_t(void* ptr){
    std::bitset<64> bits(*(int64_t*)ptr);
    // return bits.to_string();
    std::string serialize_parse;
    // uint64_t value = bits.test();
    uint64_t value = bits.to_ullong();

    serialize_parse += (value >> 56);
    serialize_parse += (value >> 48);
    serialize_parse += (value >> 40);
    serialize_parse += (value >> 32);
    serialize_parse += (value >> 24);
    serialize_parse += (value >> 16);  
    serialize_parse += (value >> 8);
    serialize_parse += (value >> 0);
    
    return serialize_parse;
}

std::string serialize_uint64_t(void* ptr){
    std::bitset<64> bits(*(uint64_t*)ptr);
    // return bits.to_string();
    std::string serialize_parse;
    // uint64_t value = bits.test();
    uint64_t value = bits.to_ullong();
    
    serialize_parse += (value >> 56);
    serialize_parse += (value >> 48);
    serialize_parse += (value >> 40);
    serialize_parse += (value >> 32);
    serialize_parse += (value >> 24);
    serialize_parse += (value >> 16);  
    serialize_parse += (value >> 8);
    serialize_parse += (value >> 0);

    return serialize_parse;
}

std::string serialize_double(void* ptr){
    union {
        double _double;
        uint64_t _int;
    } data;
    data._double = *(double*)ptr;
    std::bitset<64> bits(data._int);
    // return bits.to_string(
    std::string serialize_parse;
    uint64_t value = bits.to_ullong();
    
    serialize_parse += (value >> 56);
    serialize_parse += (value >> 48);
    serialize_parse += (value >> 40);
    serialize_parse += (value >> 32);
    serialize_parse += (value >> 24);
    serialize_parse += (value >> 16);  
    serialize_parse += (value >> 8);
    serialize_parse += (value >> 0);

    return serialize_parse;
}

std::string serialize_array(void* ptr, uint8_t type, uint32_t size){
    // omp_set_num_threads(16);
    std::string serialized;
    serialized += serialize_uint32_t(&size);
    uint8_t size_of_type = get_size(type);
    std::function<std::string(void*)> func = get_serialize_func(type);
    // #pragma omp parallel for
    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < size; i++){
        // int index = omp_get_thread_num();
        void* ptr_to_type = (void*)((uint8_t*)ptr + i * size_of_type / 8);
        serialized += func(ptr_to_type);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    // std::cout << "serialize time: " << duration.count() << std::endl;
    return serialized;
}

std::string serialize_string(void* ptr){
    
    std::string* str = (std::string*)ptr;
    // std::cout << "serialize_string: " << str->size() << std::endl;
    // str->resize(ptr);

    
    // char *cstr = new char[str->length() + 1];
    // strcpy(cstr, str->c_str());
    return serialize_array(str->data(), CHAR, str->length());
}

std::string serialize_vector(void* ptr, uint8_t type){
    std::string serialized;
    if(type != CHAR){
        switch(get_size(type)){
            case 8: {
                std::vector<uint8_t>* vc = (std::vector<uint8_t>*)ptr;
                serialized += serialize_array(vc->data(), type, vc->size());
            }; break;
            case 16: {
                std::vector<uint16_t>* vc = (std::vector<uint16_t>*)ptr;
                serialized += serialize_array(vc->data(), type, vc->size());
            }; break;
            case 32: {
                std::vector<uint32_t>* vc = (std::vector<uint32_t>*)ptr;
                serialized += serialize_array(vc->data(), type, vc->size());
            }; break;
            case 64: {
                std::vector<uint64_t>* vc = (std::vector<uint64_t>*)ptr;
                serialized += serialize_array(vc->data(), type, vc->size());
            }; break;
        }
    }

    return serialized;
}

std::string serialize_struct(struct metadatas* meta) {
    // std::cout << "serialize_struct" << std::endl;
    std::string serialized = "";

    for(auto fields : meta->key_fields) {
        uint8_t type = meta->type_fields[fields];
        void* ptr = meta->ptr_fields[fields];

        if(type == OBJECT){
            serialized += serialize_struct((struct metadatas*)ptr);
        } else if(type == STRING){
            // std::cout << "serialize string" << std::endl;
            serialized += serialize_string(ptr);
        } else if(type > ARRAY){
            serialized += serialize_vector(ptr, type - ARRAY);
        } else{
            serialized += get_serialize_func(type)(ptr);
        }
    }

    // for(int i = 0; i < serialized.size(); i++){
    //     std::bitset<8> bits(serialized[i]);
    // }
    return serialized;
}
