#ifndef STRUCT_H
#define STRUCT_H
#include "include.h"

typedef struct data
{
    long int* backup;
    long int* memory;
    int length;
    int intruction_pointer;
    int relative_base;
} DATA;

#endif