#include "request.hpp"

Request::Request(uint8_t a, uint8_t b){
    this->a = a;
    this->b = b;
    
    meta.key_fields.push_back("a");
    meta.key_fields.push_back("b");
    
    meta.type_fields["a"] = UINT8_T;
    meta.type_fields["b"] = UINT8_T;
    
    meta.ptr_fields["a"] =  &this->a;
    meta.ptr_fields["b"] =  &this->b;
}


Request::Request(){
    meta.key_fields.push_back("a");
    meta.key_fields.push_back("b");
    
    meta.type_fields["a"] = UINT8_T;
    meta.type_fields["b"] = UINT8_T;
    
    meta.ptr_fields["a"] =  &this->a;
    meta.ptr_fields["b"] =  &this->b;
}

std::string Request::serialize(){
    std::string ss = serialize_struct(&meta);
    std::string serialize;
    for(auto i : ss){
        serialize += std::bitset<8>(i).to_string();
    }

    return serialize;
}


void Request::deserialize(std::string data){
    std::string ss;
    for(int i = 0; i < data.length(); i += 8){
        ss += (char)std::bitset<8>(data.substr(i, 8)).to_ulong();
    }
    unserialize_struct(ss, &meta);
}