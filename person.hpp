#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>
#include <bitset>
#include "include/tools/tools.hpp"
#include "include/serialize/serialize.hpp"
#include "include/unserialize/unserialize.hpp"

class Person { 
    public: 
        struct metadatas meta;
        Person(uint8_t age, std::string name, Person &father);
        Person(uint8_t age, std::string name);
        Person();
        Person(Person& father);

        std::string serialize();
        void deserialize(std::string data);

        uint8_t age;
        std::string name;
        Person* father;
};

#endif