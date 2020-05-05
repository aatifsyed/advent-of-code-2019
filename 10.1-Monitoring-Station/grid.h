#ifndef GRID_H
#define GRID_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

void print_byte(char byte, bool newline)
{
    printf("%c", (byte & 0b10000000) ? '1' : '0');
    printf("%c", (byte & 0b01000000) ? '1' : '0');
    printf("%c", (byte & 0b00100000) ? '1' : '0');
    printf("%c", (byte & 0b00010000) ? '1' : '0');
    printf("%c", (byte & 0b00001000) ? '1' : '0');
    printf("%c", (byte & 0b00000100) ? '1' : '0');
    printf("%c", (byte & 0b00000010) ? '1' : '0');
    printf("%c", (byte & 0b00000001) ? '1' : '0');
    if (newline)
    {
        printf("\n");
    }
}

char** _create_char_grid(int x_max, int y_max)
{
    // create an array of pointers. These will be possible values of x
    char** x_values = NULL;
    x_values = (char**) malloc(x_max * sizeof(char*));
    memset(x_values, 0, x_max * sizeof(char*));

    // for each column in that row, create an array for all possible values of y
    for (int x = 0; x < x_max; x++)
    {
        x_values[x] = (char*) malloc(y_max * sizeof(char));
        memset(x_values[x], 0, y_max * sizeof(char));
    }

    return x_values;
}

void _destroy_char_grid(char*** grid, int x_max)
{
    for (int x = 0; x < x_max; x++)
    {
        free((*grid)[x]);
    }
    free(*grid);
    *grid = NULL;
}

void _print_char_grid(char** grid, int x_max, int y_max)
{
    printf("x+ →, y+ ↓\n");
    printf("\033[2;33m"); // red    
    // note, we do y's first, since a line of printed text is constant y
    for (int y = 0; y < y_max; y++)
    {
        for (int x = 0; x < x_max; x++)
        {
            printf("%d", grid[x][y]);
        }
        printf("\n");
    }
    printf("\033[0m"); // reset
}

typedef struct grid
{
    char** grid;
    int x_max;
    int y_max;
} GRID;

GRID* create_grid(int x_max, int y_max)
{
    GRID* grid = NULL;
    grid = (GRID*) malloc(sizeof(GRID));

    grid->grid = _create_char_grid(x_max, y_max);
    grid->x_max = x_max;
    grid->y_max = y_max;

    assert(grid != NULL);
    return grid;
}

void destroy_grid(GRID** grid)
{
    _destroy_char_grid( &((*grid)->grid), (*grid)->x_max);
    free(*grid);
    *grid = NULL;
}

void print_grid(GRID* grid)
{
    _print_char_grid(grid->grid, grid->x_max, grid->y_max);
}
#endif