#include <string>
#include <functional>
#include <bitset>
#include <iostream>
#include <map>

#define INT8_T      0x1
#define UINT8_T     0x2
#define CHAR        0x3
#define BOOL        0x4
#define INT16_T     0x5
#define UINT16_T    0x6
#define INT32_T     0x7
#define UINT32_T    0x8
#define FLOAT       0x9
#define INT64_T     0xA
#define UINT64_T    0xB
#define DOUBLE      0xC
#define ARRAY       0xF

void unserialize_int8_t(std::string str, void* ptr);
void unserialize_uint8_t(std::string str, void* ptr);
void unserialize_char(std::string str, void* ptr);
void unserialize_bool(std::string str, void* ptr);
void unserialize_int16_t(std::string str, void* ptr);
void unserialize_uint16_t(std::string str, void* ptr);
void unserialize_int32_t(std::string str, void* ptr);
void unserialize_uint32_t(std::string str, void* ptr);
void unserialize_float(std::string str, void* ptr);
void unserialize_int64_t(std::string str, void* ptr);
void unserialize_uint64_t(std::string str, void* ptr);
void unserialize_double(std::string str, void* ptr);
void unserialize_array(std::string str, void* ptr, uint8_t type);

