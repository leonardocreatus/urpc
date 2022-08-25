#include <serialize/serialize.hpp>
#include <unserialize/unserialize.hpp>
#include <tools/tools.hpp>
#include <string>
#include <iostream>
#include <map>
#include <vector>

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
        uint8_t type = meta->type_fields[fields];
        void* ptr = meta->ptr_fields[fields];
        
        if(type == STRUCT){
            serialized += serialize_struct_person((struct Person*)(ptr));
        }else {
            std::function<std::string(void*)> func = get_serialize_func(type);
            serialized += func(ptr);
        }
    }
    return serialized;
}

void unserialize_struct(std::string& serialized, struct metadatas* metadata) {
    for(auto fields : metadata->key_fields) {
        uint8_t type = metadata->type_fields[fields];
        void* ptr = metadata->ptr_fields[fields];
        if(type == STRUCT){
            struct Person* p = (struct Person*)ptr;
            unserialize_struct(serialized, p->metadata);
        }else {
            std::function<void(std::string& str, void*)> func = get_unserialize_func(type);
            func(serialized, ptr);
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
    father.name = "pessoa 2 asihaushuas";

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
    
    p2.metadata->ptr_fields["father"] = &father2;
    p2.father = &father2;
    
    unserialize_struct(serialized, p2.metadata);
    printf("%d\n", p2.father->age);
    printf("%s\n", p2.father->name.c_str());
    std::cout << p2.father->name << std::endl;


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
