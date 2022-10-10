#ifndef DATA_S_H
#define DATA_S_H

#include <sys/types.h>

struct data_s {
    uint32_t tid;
    uint32_t seq;
    uint32_t parts;
};

#endif