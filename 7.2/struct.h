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
    int phase;
    bool phase_has_been_inputted;
    bool has_halted;
} DATA;

#endif