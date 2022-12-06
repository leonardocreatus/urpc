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
        
        Request(std::string str);
        Request();

        ~Request();

        std::string serialize();
        void deserialize(std::string data);

        std::string str;
};

#endif