#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <string>
#include <bitset>
#include <vector>

#include "include/tools/tools.hpp"
#include "include/serialize/serialize.hpp"
#include "include/unserialize/unserialize.hpp"

class Response { 
    public: 
        struct metadatas meta;
        
        Response(uint16_t x);
        Response();

        std::string serialize();
        void deserialize(std::string data);

        uint16_t x;
};

#endif