#include "file.h"
#include "grid.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ASTEROID 0b00100011
#define SPACE    0b00101110
#define HIDDEN   0b01000000

GRID* create_map(char* filename)
{
    int x_max = 0;
    int y_max = 0;
    GRID* map = NULL;
    FILE* file = NULL;

    file = fopen(filename, "r");
    assert(file != NULL);

    map = create_grid(x_max, y_max);
    
    

    fclose(file);
    return map;
}

void fill_map(FILE* file, GRID* map)
{
    char c = '\0';

    fseek(file, 0, SEEK_SET);

    for(int y = 0; y < map->y_max; y++)
    {
        for (int x = 0; x < map->x_max; x++)
        {
            while( (c = fgetc(file)) != '\n')
            map->grid[x][y] = fgetc(file);
        }
    }
}

void destroy_map(GRID** map)
{
    destroy_grid(map);
}

int main()
{
    printf("Observable asteroid: %c\n", ASTEROID );
    printf("    Hidden asteroid: %c\n", ASTEROID | HIDDEN);
    printf("   Observable space: %c\n", SPACE );
    printf("       Hidden space: %c\n", SPACE | HIDDEN);
    print_byte(EOF, false);
}