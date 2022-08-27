#include <serialize/serialize.hpp>
#include <unserialize/unserialize.hpp>
#include <tools/tools.hpp>
#include <string>
#include <iostream>
#include <map>
#include <vector>



struct Person {
    struct metadatas metadata;
    uint8_t age;
    std::string name;
    struct Person* father;
};


// std::string serialize_struct_person(struct Person* person);
// std::string serialize_struct(struct metadatas* meta);

// std::string serialize_struct_person(struct Person* person){
//     return serialize_struct(person->metadata);
// }

std::string serialize_struct(struct metadatas* meta) {
    std::string serialized = "";
    // std::cout << "serialize_struct" << std::endl;
    // printf("meta->key_fields.size() = %lu\n", meta->key_fields.size());
    // printf("meta pointer: %p\n", meta);
    for(auto fields : meta->key_fields) {
        // std::cout << "fields: " << fields << std::endl;
        uint8_t type = meta->type_fields[fields];
        void* ptr = meta->ptr_fields[fields];
        printf("ptr: %p\n", ptr);

        if(type == STRUCT){
            // std::cout << "struct" << std::endl;
            // printf("ptr: %p\n", ptr);
            serialized += serialize_struct((struct metadatas*)ptr);
            // serialized += serialize_struct_person((struct Person*)(ptr));
        }else {
            // std::cout << "not struct" << std::endl;
            std::function<std::string(void*)> func = get_serialize_func(type);
            serialized += func(ptr);
        }
    }
    return serialized;
}

void unserialize_struct(std::string& serialized, struct metadatas* metadata) {
    for(auto fields : metadata->key_fields) {
        std::cout << "fields: " << fields << std::endl;
        printf("ptr: %p\n", metadata->ptr_fields[fields]);
        uint8_t type = metadata->type_fields[fields];
        void* ptr = metadata->ptr_fields[fields];
        if(type == STRUCT){
            unserialize_struct(serialized, (struct metadatas*)ptr);
            // struct Person* p = (struct Person*)ptr;
            // unserialize_struct(serialized, p->metadata);
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

    // struct metadatas meta1;
    p.metadata.key_fields.push_back("age");
    p.metadata.key_fields.push_back("name");
    p.metadata.key_fields.push_back("father");

    p.metadata.type_fields["age"] = UINT8_T;
    p.metadata.type_fields["name"] = STRING;
    p.metadata.type_fields["father"] = STRUCT;

    p.metadata.ptr_fields["age"] = &p.age;
    p.metadata.ptr_fields["name"] = &p.name[0];
    


    struct Person p2;
    p2.age = 20;
    p2.name = "pessoa 2";
    p2.metadata.key_fields.push_back("age");
    p2.metadata.key_fields.push_back("name");
    p2.metadata.type_fields["age"] = UINT8_T;
    p2.metadata.type_fields["name"] = STRING;
    p2.metadata.ptr_fields["age"] = &p2.age;
    p2.metadata.ptr_fields["name"] = &p2.name[0];

    p.father = &p2;


    p.metadata.ptr_fields["father"] = &p2;

    printf("p.metadata.ptr_fields[\"father\"] = %p\n", p.metadata.ptr_fields["father"]);
    printf("p.father = %p\n", p.father);
    printf("p2 = %p\n", &p2);
    printf("p.metadata.key_fields = %p\n", &p.metadata.key_fields);
    printf("p.metadata.type_fields = %p\n", &p.metadata.type_fields);
    printf("p.metadata.ptr_fields = %p\n", &p.metadata.ptr_fields);
    printf("p.metadata.ptr_fields[\"age\"] = %p\n", &p.metadata.ptr_fields["age"]);
    printf("p.metadata.ptr_fields[\"age\"] = %p\n", p.metadata.ptr_fields["age"]);


    std::string serialized = serialize_struct(&p.metadata);
    std::cout << serialized << std::endl;

    // unserialize_struct(serialized, &meta2);
    // printf("age: %d, name: %s\n", p2.age, p2.name.c_str());

    struct Person p3;
    p3.name = "haha";

    printf("pointer name: %p\n", &p3.name);
    printf("pointer[0]: %p\n", &p3.name[0]);
    printf("pointer[1]: %p\n", &p3.name[1]);
    printf("pointer[2]: %p\n", &p3.name[2]);
    printf("pointer[3]: %p\n", &p3.name[3]);

    p3.metadata.key_fields.push_back("age");
    p3.metadata.key_fields.push_back("name");
    p3.metadata.key_fields.push_back("father");
    p3.metadata.type_fields["age"] = UINT8_T;
    p3.metadata.type_fields["name"] = STRING;
    p3.metadata.type_fields["father"] = STRUCT;

    p3.metadata.ptr_fields["age"] = &p3.age;
    p3.metadata.ptr_fields["name"] = &p3.name;
    


    struct Person p4;
    p4.metadata.key_fields.push_back("age");
    p4.metadata.key_fields.push_back("name");

    p4.metadata.type_fields["age"] = UINT8_T;
    p4.metadata.type_fields["name"] = STRING;

    p4.metadata.ptr_fields["age"] = &p4.age;
    p4.metadata.ptr_fields["name"] = &p4.name;

    p3.metadata.ptr_fields["father"] = &p4;
    p3.father = &p4;


    unserialize_struct(serialized, &p3.metadata);
    printf("age: %d, name: %s\n", p3.age, p3.name.c_str());
    printf("age: %d, name: %s\n", p3.father->age, p3.father->name.c_str());


    // p.metadata->key_fields.push_back("age");
    // p.metadata->type_fields["age"] = UINT8_T ;
    // p.metadata->ptr_fields["age"] = &p.age;

    // p.metadata->key_fields.push_back("name");
    // p.metadata->type_fields["name"] = STRING ;
    // p.metadata->ptr_fields["name"] = &p.name;

    // p.metadata->key_fields.push_back("father");
    // p.metadata->type_fields["father"] = STRUCT;

    // struct Person father;
    // father.age = 27;
    // father.name = "pessoa 2 asihaushuas";

    // father.metadata = new struct metadatas;

    // father.metadata->key_fields.push_back("age");
    // father.metadata->type_fields["age"] = UINT8_T ;
    // father.metadata->ptr_fields["age"] = &father.age;

    // father.metadata->key_fields.push_back("name");
    // father.metadata->type_fields["name"] = STRING ;
    // father.metadata->ptr_fields["name"] = &father.name;

    // p.father = &father;
    // p.metadata->ptr_fields["father"] = p.father;
    
    // std::string serialized = serialize_struct(p.metadata);


    // struct Person p2;
    // p2.metadata = new struct metadatas;
    
    // p2.metadata->key_fields.push_back("age");
    // p2.metadata->type_fields["age"] = UINT8_T ;
    // p2.metadata->ptr_fields["age"] = &p2.age;

    // p2.metadata->key_fields.push_back("name");
    // p2.metadata->type_fields["name"] = STRING ;
    // p2.metadata->ptr_fields["name"] = &p2.name;

    // p2.metadata->key_fields.push_back("father");
    // p2.metadata->type_fields["father"] = STRUCT;

    // struct Person father2;
    // father2.metadata = new struct metadatas;

    // father2.metadata->key_fields.push_back("age");
    // father2.metadata->type_fields["age"] = UINT8_T ;
    // father2.metadata->ptr_fields["age"] = &father2.age;

    // father2.metadata->key_fields.push_back("name");
    // father2.metadata->type_fields["name"] = STRING ;
    // father2.metadata->ptr_fields["name"] = &father2.name;
    
    // p2.metadata->ptr_fields["father"] = &father2;
    // p2.father = &father2;
    
    // unserialize_struct(serialized, p2.metadata);
    // printf("%d\n", p2.father->age);
    // printf("%s\n", p2.father->name.c_str());
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

    printf("people pointer: %p\n", &p);
    printf("metadada pointer: %p\n", &p.metadata);
    // void* ptr = &p;

    // int* iptr = static_cast<int*>(ptr);

    // printf("people pointer: %d\n", *iptr);
    // void* ptr2 = p.metadata;

    // void* ptr_aux = (void*)((uint8_t*)ptr - (uint8_t*)ptr2);
    // printf("people pointer: %p\n", ptr_aux);
    // printf("people value: %lld\n", value);
    // printf("people pointer: %lld\n", pointer_p);
    // int dif = &p.metadata - &ptr;
    // printf("dif: %d\n", dif);
    // printf("void pointer: %p\n", ptr);
    // printf("void pointer -> meta: %p\n", ptr->metadata);
    
}                    
