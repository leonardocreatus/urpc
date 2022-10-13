#include "file.hpp"

File::File(std::string name, std::string content){
    this->name = name;
    this->content = content;
    
    meta.key_fields.push_back("name");
    meta.type_fields["name"] = STRING;
    meta.ptr_fields["name"] =  &this->name;

    meta.key_fields.push_back("content");
    meta.type_fields["content"] = STRING;
    meta.ptr_fields["content"] =  &this->content;

}

File::File(){
    meta.key_fields.push_back("name");
    meta.type_fields["name"] = STRING;
    meta.ptr_fields["name"] =  &this->name;

    meta.key_fields.push_back("content");
    meta.type_fields["content"] = STRING;
    meta.ptr_fields["content"] =  &this->content;
}

std::string File::serialize(){
    std::string ss = serialize_struct(&meta);
    std::cout << "ss size: " << ss.size() << std::endl;
    std::string serialize = ss;
    // for(int i = 0; i < ss.length(); i += 8){
    //     serialize += std::bitset<8>(ss.substr(i, i + 8)).to_ulong();
    // }
    std::cout << "serialize size: " << serialize.size() << std::endl;
    return serialize; 
}


void File::deserialize(std::string data){
    std::string ss;
    for(int i = 0; i < data.length(); i++){
        ss += std::bitset<8>(data[i]).to_string();
    }
    unserialize_struct(ss, &meta);
}



/*
in.txt
content size: 2
printfilename
file name: in.txt
type: 18
field: name
str size: 6
type: 18
field: content
str size: 2
serialized
ss size: 128

serialize size: 16
size msg: 17
parts: 1
payload: 
count: 0 parts: 1
22
newfilename: in.txt.copy
*/