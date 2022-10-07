#include "person.hpp"


Person::Person(uint8_t age, std::string name, Person &father) {
        this->age = age;
        this->name = name;
        this->father = &father;
        
        meta.key_fields.push_back("age");
        meta.key_fields.push_back("name");
        meta.key_fields.push_back("father");
        
        meta.type_fields["age"] = UINT8_T;
        meta.type_fields["name"] = STRING;
        meta.type_fields["father"] = OBJECT;
        
        meta.ptr_fields["age"] =  &this->age;
        meta.ptr_fields["name"] =  &this->name;
        meta.ptr_fields["father"] =  this->father;
}

Person::Person(uint8_t age, std::string name) {
        this->age = age;
        this->name = name;
        
        meta.key_fields.push_back("age");
        meta.key_fields.push_back("name");
        
        meta.type_fields["age"] = UINT8_T;
        meta.type_fields["name"] = STRING;
        
        meta.ptr_fields["age"] =  &this->age;
        meta.ptr_fields["name"] =  &this->name;
}

Person::Person(){
        meta.key_fields.push_back("age");
        meta.key_fields.push_back("name");
        
        meta.type_fields["age"] = UINT8_T;
        meta.type_fields["name"] = STRING;
        
        meta.ptr_fields["age"] =  &this->age;
        meta.ptr_fields["name"] =  &this->name;
}

Person::Person(Person& father){
        this->father = &father;
        
        
        meta.key_fields.push_back("age");
        meta.key_fields.push_back("name");
        meta.key_fields.push_back("father");
        
        meta.type_fields["age"] = UINT8_T;
        meta.type_fields["name"] = STRING;
        meta.type_fields["father"] = OBJECT;
        
        meta.ptr_fields["age"] =  &this->age;
        meta.ptr_fields["name"] =  &this->name;
        meta.ptr_fields["father"] =  this->father;
}

std::string Person::serialize(){
        std::string ss = serialize_struct(&meta);
        std::string serialize;
        for(int i = 0; i < ss.length(); i += 8){
                serialize += std::bitset<8>(ss.substr(i, i + 8)).to_ulong();
        }
        // std::string serialize = ss;
        return serialize; 
}

void Person::deserialize(std::string data){
        std::string ss;
        for(int i = 0; i < data.length(); i++){
                ss += std::bitset<8>(data[i]).to_string();
        }
        // ss = data;
        unserialize_struct(ss, &meta);
}