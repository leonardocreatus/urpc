#include <string>
#include <functional>
#include <bitset>
#include <iostream>
#include <cstring>
#include <map>
#include "./../tools/tools.hpp"

void unserialize_int8_t(std::string& str, void* ptr);
void unserialize_uint8_t(std::string& str, void* ptr);
void unserialize_char(std::string& str, void* ptr);
void unserialize_bool(std::string& str, void* ptr);
void unserialize_int16_t(std::string& str, void* ptr);
void unserialize_uint16_t(std::string& str, void* ptr);
void unserialize_int32_t(std::string& str, void* ptr);
void unserialize_uint32_t(std::string& str, void* ptr);
void unserialize_float(std::string& str, void* ptr);
void unserialize_int64_t(std::string& str, void* ptr);
void unserialize_uint64_t(std::string& str, void* ptr);
void unserialize_double(std::string& str, void* ptr);
void unserialize_array(std::string& str, void* ptr, uint8_t type);
void unserialize_string(std::string& str, void* ptr);

std::function<void(std::string& str, void*)> get_unserialize_func(uint8_t type);
void unserialize_struct(std::string& serialized, struct metadatas* metadata);

