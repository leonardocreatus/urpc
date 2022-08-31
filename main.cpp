#include <serialize/serialize.hpp>
#include <unserialize/unserialize.hpp>
#include <tools/tools.hpp>
#include <string>
#include <iostream>
#include <map>
#include <typeinfo>
#include <iterator>
#include <array>
#include <any>
#include <vector>


class Value {
    public:
        struct metadatas metadata;
        Value(float a, float b, float c){
            values.push_back(a);
            values.push_back(b);
            values.push_back(c);

            
            metadata.key_fields.push_back("values");
            metadata.type_fields["values"] = FLOAT + ARRAY;
            metadata.ptr_fields["values"] = &values;
        }

        Value(){
            metadata.key_fields.push_back("values");
            metadata.type_fields["values"] = FLOAT + ARRAY;
            metadata.ptr_fields["values"] = &values;
        }

        std::vector<float> values;
};

class Person {
    public:
        struct metadatas metadata;
        Person(uint8_t age, std::string name, Value* value ) {
            this->age = age;
            this->name = name;
            this->value = value;

            metadata.key_fields.push_back("age");
            metadata.key_fields.push_back("name");
            metadata.key_fields.push_back("value");

            metadata.type_fields["age"] = UINT8_T;
            metadata.type_fields["name"] = STRING;
            metadata.type_fields["value"] = STRUCT;

            metadata.ptr_fields["age"] =  &this->age;
            metadata.ptr_fields["name"] =  &this->name;
            metadata.ptr_fields["value"] =  this->value;
        }

        Person() {
            // this->age = age;
            // this->name = name;
            this->value = new Value();

            metadata.key_fields.push_back("age");
            metadata.key_fields.push_back("name");
            metadata.key_fields.push_back("value");

            metadata.type_fields["age"] = UINT8_T;
            metadata.type_fields["name"] = STRING;
            metadata.type_fields["value"] = STRUCT;

            metadata.ptr_fields["age"] =  &this->age;
            metadata.ptr_fields["name"] =  &this->name;
            metadata.ptr_fields["value"] =  this->value;
        }

        uint8_t age;
        std::string name;
        Value* value;
};



// std::map<uint8_t, typename _Tp> map_type_to_value = {
//     {INT8_T, int8_t},
//     {UINT8_T, uint8_t},
// };

int main(int argc, char** argv){

    Value v(1.0, 2.0, 3.0);
    Person p(10, "toto", &v);
    std::string serialized = serialize_struct(&p.metadata);
    std::cout << serialized << std::endl;

    Person p2;
    unserialize_struct(serialized, &p2.metadata);
    printf("age: %d\n", p2.age);
    printf("name: %s\n", p2.name.c_str());
    std::cout << p2.name.c_str() << std::endl;
    printf("value: %f\n", p2.value->values[0]);
    printf("value: %f\n", p2.value->values[1]);
    printf("value: %f\n", p2.value->values[2]);
    

}                    

 


/*

00000000000000000000000000000010
11010000
01110010

00000000000000000000000000000010
00000001
00000010


00000000000000000000000000001000
00000000000000010000000000000000
00000000000000100000000000000000
00000000000000110000000000000000
00000000000001000000000000000000
*/