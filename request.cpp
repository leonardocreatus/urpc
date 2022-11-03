#include "request.hpp"

Request::Request(std::string str){
    this->str = str;

    meta.key_fields.push_back("str");
    meta.type_fields["str"] = STRING;
    meta.ptr_fields["str"] =  &this->str;
    std::cout << "Request ptr: " << &this->str << std::endl;
}


Request::Request(){

    this->str = "";
    meta.key_fields.push_back("str");
    meta.type_fields["str"] = STRING;
    meta.ptr_fields["str"] =  &this->str;
    std::cout << "Requestb ptr: " << &this->str << std::endl;
}

Request::~Request(){

}

std::string Request::serialize(){
    return serialize_struct(&meta);
}


void Request::deserialize(std::string data){
    unserialize_struct(data, &meta);
}
