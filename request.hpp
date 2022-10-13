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
        
        Request(std::vector<float> vec);
        Request();

        std::string serialize();
        void deserialize(std::string data);

        std::vector<float> vec;
};

#endif