#include <string>
#include <functional>
#include <bitset>
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
std::string serialize_string(std::string* str);