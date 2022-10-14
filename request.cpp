#include "request.hpp"

Request::Request(std::vector<double> vec){
    this->vec = vec;
    meta.key_fields.push_back("vec");
    meta.type_fields["vec"] = ARRAY + DOUBLE;
    meta.ptr_fields["vec"] =  &this->vec;
    std::cout << "vec size: " << vec.size() << std::endl;
}


Request::Request(){
    meta.key_fields.push_back("vec");
    meta.type_fields["vec"] = ARRAY + DOUBLE;
    meta.ptr_fields["vec"] =  &this->vec;
}

std::string Request::serialize(){
    return serialize_struct(&meta);
}


void Request::deserialize(std::string data){
    unserialize_struct(data, &meta);
}