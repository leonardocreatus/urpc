#include <string>
#include <functional>
#include <bitset>
#include <iostream>
#include <map>
#include <cstring>
#include "./../tools/tools.hpp"



std::string serialize_int8_t(void* ptr);
std::string serialize_uint8_t(void* ptr);
std::string serialize_char(void* ptr);
std::string serialize_bool(void* ptr);
std::string serialize_int16_t(void* ptr);
std::string serialize_uint16_t(void* ptr);
std::string serialize_int32_t(void* ptr);
std::string serialize_uint32_t(void* ptr);
std::string serialize_float(void* ptr);
std::string serialize_int64_t(void* ptr);
std::string serialize_uint64_t(void* ptr);
std::string serialize_double(void* ptr);
std::string serialize_array(void* ptr, uint8_t type, uint32_t size);
std::string serialize_string(void* ptr);

std::function<std::string(void*)> get_serialize_func(uint8_t type);
std::string serialize_struct(struct metadatas* meta);