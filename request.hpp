#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <string>
#include <bitset>
#include <vector>

#include "include/tools/tools.hpp"
#include "include/serialize/serialize.hpp"
#include "include/unserialize/unserialize.hpp"

class Request { 
    public: 
        struct metadatas meta;
        
        Request(uint8_t a, uint8_t b);
        Request();

        std::string serialize();
        void deserialize(std::string data);

        uint8_t a;
        uint8_t b;
};

#endif