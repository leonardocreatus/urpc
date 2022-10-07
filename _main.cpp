#include <string>
#include <iostream>
#include <map>
#include <typeinfo>
#include <iterator>
#include <array>
#include <any>
#include <vector>

#include "person.hpp"

int main(int argc, char** argv){

    Person p1(41, "Leandro"); // 1 + 4 + 7 = 12
    Person f1(23, "Leonardo", p1); // 1 + 4 + 8 = 13

    std::string serialize = f1.serialize();
    std::cout << serialize << std::endl;
    std::cout << "size: " << serialize.size() << std::endl;

    printf("----------------------------------------\n");
    printf("[p1] metadata: %p\n", &p1.meta);
    printf("[p1] metadata key_fields: %p\n", &p1.meta.key_fields);
    printf("[p1] metadata type_fields: %p\n", &p1.meta.type_fields);
    printf("[p1] metadata ptr_fields: %p\n", &p1.meta.ptr_fields);


    printf("    [p1] metadata key_fields[0]: %p\n", &p1.meta.key_fields[0]);
    printf("    [p1] metadata key_fields[1]: %p\n", &p1.meta.key_fields[1]);

    printf("    [p1] metadata type_fields name: %p\n", &p1.meta.type_fields["name"]);
    printf("    [p1] metadata type_fields age: %p\n", &p1.meta.type_fields["age"]);

    printf("    [p1] metadata ptr_fields name: %p\n", &p1.meta.ptr_fields["name"]);
    printf("    [p1] metadata ptr_fields age: %p\n", &p1.meta.ptr_fields["age"]);

    printf("[p1] age: %p\n", &p1.age);
    printf("[p1] name: %p\n", &p1.name);
    printf("[p1]    name[0]: %p\n", &p1.name[0]);
    printf("[p1]    name[size - 1]: %p\n", &p1.name[p1.name.size() - 1]);

    printf("----------------------------------------\n");
    printf("[f1] metadata: %p\n", &f1.meta);
    printf("[f1] metadata key_fields: %p\n", &f1.meta.key_fields);
    printf("[f1] metadata type_fields: %p\n", &f1.meta.type_fields);
    printf("[f1] metadata ptr_fields: %p\n", &f1.meta.ptr_fields);

    printf("    [f1] metadata key_fields[0]: %p\n", &f1.meta.key_fields[0]);
    printf("    [f1] metadata key_fields[1]: %p\n", &f1.meta.key_fields[1]);
    printf("    [f1] metadata key_fields[2]: %p\n", &f1.meta.key_fields[2]);

    printf("    [f1] metadata type_fields name: %p\n", &f1.meta.type_fields["name"]);
    printf("    [f1] metadata type_fields age: %p\n", &f1.meta.type_fields["age"]);
    printf("    [f1] metadata type_fields father: %p\n", &f1.meta.type_fields["father"]);

    printf("    [f1] metadata ptr_fields name: %p\n", &f1.meta.ptr_fields["name"]);
    printf("    [f1] metadata ptr_fields age: %p\n", &f1.meta.ptr_fields["age"]);
    printf("    [f1] metadata ptr_fields father: %p\n", &f1.meta.ptr_fields["father"]);

    printf("[f1] age: %p\n", &f1.age);
    printf("[f1] name: %p\n", &f1.name);
    printf("[f1]    name[0]: %p\n", &f1.name[0]);
    printf("[f1]    name[size - 1]: %p\n", &f1.name[f1.name.size() - 1]);
    printf("[f1] father: %p\n", f1.father);
    printf("[f1] father: %p\n", &f1.father);
        
    printf("----------------------------------------\n");

    Person p2;
    Person f2(p2);
    f2.deserialize(serialize);

    printf("p2.age: %d\n", p2.age);
    printf("p2.name: %s\n", p2.name.c_str());
    printf("f2.age: %d\n", f2.age);
    printf("f2.name: %s\n", f2.name.c_str());

}                    