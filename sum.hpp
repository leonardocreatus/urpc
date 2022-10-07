#ifndef SUM_HPP
#define SUM_HPP

#include <string>
#include <bitset>
#include <vector>

#include "include/tools/tools.hpp"
#include "include/serialize/serialize.hpp"
#include "include/unserialize/unserialize.hpp"

class Sum { 
    public: 
        struct metadatas meta;
        
        Sum(std::vector<int32_t> values);
        Sum();

        std::string serialize();
        void deserialize(std::string data);

        std::vector<int32_t> values;
};

#endif