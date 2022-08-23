#include <serialize/serialize.hpp>
#include <unserialize/unserialize.hpp>
#include <string>
#include <iostream>
#include <map>
#include <vector>

std::map<uint8_t, std::function<std::string(void*)>> __map_type_to_serialize = {
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

std::map<uint8_t, std::function<void(std::string& str, void*)>> __map_type_to_unserialize= {
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

struct metadatas {
    std::vector<std::string> key_fields;
    std::map<std::string, uint8_t> type_fields;
    std::map<std::string, void*> ptr_fields;
};

struct Person {
    uint8_t age;
    std::string name;

    struct metadatas* metadata;
    struct Person* father;
};

std::string serialize_struct_person(struct Person* person);
std::string serialize_struct(struct metadatas* meta);

std::string serialize_struct_person(struct Person* person){
    return serialize_struct(person->metadata);
}

std::string serialize_struct(struct metadatas* meta) {
    std::string serialized = "";
    for(auto fields : meta->key_fields) {
        std::cout << "field: " << fields << std::endl;
        uint8_t type = meta->type_fields[fields];
        void* ptr = meta->ptr_fields[fields];
        
        if(type == STRUCT){
            serialized += serialize_struct_person((struct Person*)(ptr));
        }else {
            serialized += __map_type_to_serialize[type](ptr);
        }
    }
    return serialized;
}

void unserialize_struct(std::string& serialized, struct metadatas* metadata) {
    for(auto fields : metadata->key_fields) {
        uint8_t type = metadata->type_fields[fields];
        void* ptr = metadata->ptr_fields[fields];
    
        // if(type == STRUCT) {
        //     std::string serialized_field = serialized.substr(0, 8);
        //     struct Person* p = (struct Person*)ptr;
        //     unserialize_struct(serialized_field, p->metadata);
        // } else if(type == UINT8_T) {
        //     std::string serialized_field = serialized.substr(0, 8);
        //     unserialize_uint8_t(serialized_field, ptr);
        //     serialized = serialized.substr(8, serialized.size());
        // } else if(type == STRING) {
        //     std::cout << serialized << std::endl;
        //     // std::string serialized_field = serialized.substr(0, 8);
        //     unserialize_string(serialized, ptr);
        // }

        std::cout << "field: " << fields << std::endl;
        std::cout << serialized << std::endl;
        if(type == STRUCT){
            struct Person* p = (struct Person*)ptr;
            unserialize_struct(serialized, p->metadata);
        }else {
            printf("- ptr: %p\n", ptr);
            __map_type_to_unserialize[type](serialized, ptr);
        }
    }
    
}

int main(int argc, char** agrv){

    // std::string ss = "batata";
    // std::string serialized = serialize_string(&ss);
    // std::string serialized = "01100001001000000011000100011011000000000000000000000000000010000111000001100101011100110111001101101111011000010010000000110010";
    // std::cout << serialized << std::endl;
    // std::string ss2;
    // unserialize_string(serialized, &ss2);
    // std::cout << ss2 << std::endl;

    struct Person p;
    p.age = 10;
    p.name = "pessoa 1";

    p.metadata = new struct metadatas;
    p.metadata->key_fields.push_back("age");
    p.metadata->type_fields["age"] = UINT8_T ;
    p.metadata->ptr_fields["age"] = &p.age;

    p.metadata->key_fields.push_back("name");
    p.metadata->type_fields["name"] = STRING ;
    p.metadata->ptr_fields["name"] = &p.name;

    p.metadata->key_fields.push_back("father");
    p.metadata->type_fields["father"] = STRUCT;

    struct Person father;
    father.age = 27;
    father.name = "pessoa 2";

    father.metadata = new struct metadatas;

    father.metadata->key_fields.push_back("age");
    father.metadata->type_fields["age"] = UINT8_T ;
    father.metadata->ptr_fields["age"] = &father.age;

    father.metadata->key_fields.push_back("name");
    father.metadata->type_fields["name"] = STRING ;
    father.metadata->ptr_fields["name"] = &father.name;

    p.father = &father;
    p.metadata->ptr_fields["father"] = p.father;
    
    std::string serialized = serialize_struct(p.metadata);


    struct Person p2;
    p2.metadata = new struct metadatas;
    
    p2.metadata->key_fields.push_back("age");
    p2.metadata->type_fields["age"] = UINT8_T ;
    p2.metadata->ptr_fields["age"] = &p2.age;

    p2.metadata->key_fields.push_back("name");
    p2.metadata->type_fields["name"] = STRING ;
    p2.metadata->ptr_fields["name"] = &p2.name;

    p2.metadata->key_fields.push_back("father");
    p2.metadata->type_fields["father"] = STRUCT;

    struct Person father2;
    father2.metadata = new struct metadatas;

    father2.metadata->key_fields.push_back("age");
    father2.metadata->type_fields["age"] = UINT8_T ;
    father2.metadata->ptr_fields["age"] = &father2.age;

    father2.metadata->key_fields.push_back("name");
    father2.metadata->type_fields["name"] = STRING ;
    father2.metadata->ptr_fields["name"] = &father2.name;

    // printf("name[0]: %p\n", &father2.name[0]);
    // printf("name[1]: %p\n", &father2.name[1]);
    printf("ptr name: %p\n", father2.metadata->ptr_fields["name"]);
    
    p2.metadata->ptr_fields["father"] = &father2;
    p2.father = &father2;
    
    std::cout << serialized << std::endl;
    unserialize_struct(serialized, p2.metadata);
    printf("%d\n", p2.father->age);
    printf("%s\n", p2.father->name.c_str());
    // std::cout << p2.father->name << std::endl;


    // uint32_t a = 100;
    // int64_t  x = -100;
    // std::string ss = serialize_uint32_t(&a);
    // ss += serialize_int64_t(&x);
    // uint32_t b = 0;
    // int64_t y = 0;
    // unserialize_uint32_t(ss, &b);
    // unserialize_int64_t(ss, &y);
    // printf("%d\n", b);
    // printf("%lld\n", y);
    
}                    
