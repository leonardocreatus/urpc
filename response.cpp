#include "response.hpp"

Response::Response(uint64_t x){
    this->x = x;
    
    meta.key_fields.push_back("x");
    
    meta.type_fields["x"] = UINT64_T;
    
    meta.ptr_fields["x"] =  &this->x;
}


Response::Response(){
    meta.key_fields.push_back("x");
    
    meta.type_fields["x"] = UINT64_T;
    
    meta.ptr_fields["x"] =  &this->x;
}

std::string Response::serialize(){
    std::string ss = serialize_struct(&meta);
    return ss;
    // std::string serialize;
    // for(int i = 0; i < ss.length(); i += 8){
    //         serialize += std::bitset<8>(ss.substr(i, i + 8)).to_ulong();
    // }
    // return serialize; 
}


void Response::deserialize(std::string data){
    // std::string ss;
    // for(int i = 0; i < data.length(); i++){
    //     ss += std::bitset<8>(data[i]).to_string();
    // }
    unserialize_struct(data, &meta);
}