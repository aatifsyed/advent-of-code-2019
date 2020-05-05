#include "include.h"

Planet* add_planet(Planet* planet_head, char name[4], char orbits[4])
{
    Planet* new_planet = malloc(sizeof(Planet));

    for(int i = 0; i < 4; i++)
    {
        new_planet->name_this[i] = name[i];
        new_planet->name_orbits[i] = orbits[i];
    }

    new_planet->tree_orbits = NULL;
    new_planet->tree_orbited_by = NULL;
    new_planet->next_orbited_by = NULL;

    new_planet->next_list = planet_head;
    planet_head = new_planet;
}

Planet* file_to_planets(Planet* planet_head)
{
    char c;
    FILE* input = fopen("input", "r");
    
    while ( (c = fgetc(input)) != EOF)
    {

    }
}

int main()
{
    Planet* planet_head = NULL;
    planet_head = file_to_planets(planet_head);
}