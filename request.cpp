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
    return serialize_struct(&meta);
}


void Request::deserialize(std::string data){
    unserialize_struct(data, &meta);
}