#ifndef STRUCT_H
#define STRUCT_H

typedef struct Planet Planet;
struct Planet
{
    char name_this[4];
    char name_orbits[4];
    Planet* tree_orbits;
    Planet* tree_orbited_by;
    Planet* next_orbited_by;
    Planet* next_list;
};

#endif