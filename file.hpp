#ifndef FILE_HPP
#define FILE_HPP

#include <string>

#include "include/tools/tools.hpp"
#include "include/serialize/serialize.hpp"
#include "include/unserialize/unserialize.hpp"

class File {
    public:
        struct metadatas meta;
        
        File(std::string name);
        File();
        
        std::string serialize();
        void deserialize(std::string data);
        
        std::string name;
};

#endif