#ifndef STRUCT_H
#define STRUCT_H
#include "include.h"

typedef struct data
{
    int* saved_memory;
    int* memory;
    int length;
    int intruction_pointer; // don't modify outside of intcode();
    // not opcode etc - keeping multiple mutable values in sync can be lame
} DATA;

typedef struct permuting_int
{
    int integer;
    bool looking_right;
} PERMUTING_INT;

#endif