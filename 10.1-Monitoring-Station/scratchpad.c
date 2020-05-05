#include "grid.h"
#include <assert.h>
#include <stdio.h>

int main()
{
    GRID* testgrid = create_grid(0,0);
    destroy_grid(&testgrid);
    assert(testgrid == NULL);
}