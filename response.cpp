#include "response.hpp"

Response::Response(uint16_t x){
    this->x = x;
    
    meta.key_fields.push_back("x");
    
    meta.type_fields["x"] = UINT16_T;
    
    meta.ptr_fields["x"] =  &this->x;
}


Response::Response(){
    meta.key_fields.push_back("x");
    
    meta.type_fields["x"] = UINT16_T;
    
    meta.ptr_fields["x"] =  &this->x;
}

std::string Response::serialize(){
    std::string ss = serialize_struct(&meta);
    std::string serialize;
    for(auto i : ss){
        serialize += std::bitset<8>(i).to_string();
    }

    return serialize;
}


void Response::deserialize(std::string data){
    std::string ss;
    for(int i = 0; i < data.length(); i += 8){
        ss += (char)std::bitset<8>(data.substr(i, 8)).to_ulong();
    }
    unserialize_struct(ss, &meta);
}