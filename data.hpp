


struct Pessoa {
    uint8_t age;
};


struct data {
    std::vector<std::string> key_fields;
    std::map<std::string, uint8_t> type_fields;
    std::map<std::string, void*> ptr_fields;
};
}

struct main {
    struct Pessoa* p1;    
    struct Pessoa* p2;
};

