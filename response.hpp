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
        
        Response(float x);
        Response();

        std::string serialize();
        void deserialize(std::string data);

        float x;
};

#endif