#include "sum.hpp"


Sum::Sum(std::vector<int32_t> values){
    this->values = values;
    
    meta.key_fields.push_back("values");
    
    meta.type_fields["values"] = ARRAY + INT32_T;
    
    meta.ptr_fields["values"] =  &this->values;
}

Sum::Sum(){
    meta.key_fields.push_back("values");

    meta.type_fields["values"] = ARRAY + INT32_T;
    
    meta.ptr_fields["values"] =  &this->values;
}

std::string Sum::serialize(){
    std::string ss = serialize_struct(&meta);
    std::string serialize;
    for(int i = 0; i < ss.length(); i += 8){
            serialize += std::bitset<8>(ss.substr(i, i + 8)).to_ulong();
    }
    return serialize; 
}

void Sum::deserialize(std::string data){
    std::string ss;
    for(int i = 0; i < data.length(); i++){
            ss += std::bitset<8>(data[i]).to_string();
    }
    unserialize_struct(ss, &meta);
}