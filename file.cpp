#include "file.hpp"

File::File(std::string name){
    this->name = name;

    std::cout << "name: " << name.size() << std::endl;
    
    meta.key_fields.push_back("name");
    
    meta.type_fields["name"] = STRING;
    
    meta.ptr_fields["name"] =  &this->name;
}

File::File(){
    meta.key_fields.push_back("name");
    
    meta.type_fields["name"] = STRING;
    
    meta.ptr_fields["name"] =  &this->name;
}

std::string File::serialize(){
    std::string ss = serialize_struct(&meta);
    std::string serialize;
    for(auto i : ss){
        serialize += std::bitset<8>(i).to_string();
    }

    return serialize;
}

void File::deserialize(std::string data){
    std::string ss;
    for(int i = 0; i < data.length(); i += 8){
        ss += (char)std::bitset<8>(data.substr(i, 8)).to_ulong();
    }
    unserialize_struct(ss, &meta);
}