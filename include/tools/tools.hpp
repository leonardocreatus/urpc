#include <string>
#include <functional>
#ifndef TOOLS
#define TOOLS

#include <bitset>
#include <map>
#include <vector>

struct metadatas {
    std::vector<std::string> key_fields;
    std::map<std::string, uint8_t> type_fields;
    std::map<std::string, void*> ptr_fields;
};

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
#define STRING      0xF + 0x3 
#define STRUCT      0xE
#define ARRAY       0xF

uint8_t get_size(uint8_t type);

#endif