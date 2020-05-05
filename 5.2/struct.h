#ifndef STRUCT_H
#define STRUCT_H

typedef struct Data
{
    int* memory;
    int length;
    int intruction_pointer; // don't modify outside of intcode();
    // not opcode etc - keeping multiple mutable values in sync can be lame
} Data;

#endif