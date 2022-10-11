#include "request.hpp"

Request::Request(std::vector<uint8_t> vec){
    this->vec = vec;
    meta.key_fields.push_back("vec");
    meta.type_fields["vec"] = ARRAY + UINT8_T;
    meta.ptr_fields["vec"] =  &this->vec;
}


Request::Request(){
    meta.key_fields.push_back("vec");
    meta.type_fields["vec"] = ARRAY + UINT8_T;
    meta.ptr_fields["vec"] =  &this->vec;
}

std::string Request::serialize(){
    std::string ss = serialize_struct(&meta);
    std::string serialize;
    for(int i = 0; i < ss.length(); i += 8){
            serialize += std::bitset<8>(ss.substr(i, i + 8)).to_ulong();
    }
    return serialize; 
}


void Request::deserialize(std::string data){
    std::string ss;
    for(int i = 0; i < data.length(); i++){
        ss += std::bitset<8>(data[i]).to_string();
    }
    unserialize_struct(ss, &meta);
}