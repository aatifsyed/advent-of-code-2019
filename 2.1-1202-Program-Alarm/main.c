#include <stdio.h>
#include <stdlib.h>
#define TRACE(fmt, args...) printf(fmt, ##args);
#define ADD      1
#define MULTIPLY 2
#define STOP     99
#define ARG1     a[i + 1]
#define ARG2     a[i + 2]
#define DEST     a[i + 3]

int main()
{
    // in quartets: opcode, index of arg 1, index of arg 2, index to store answer
    int a[] = {1,0,0,3,1,1,2,3,1,3,4,3,1,5,0,3,2,13,1,19,1,19,9,23,1,5,23,27,1,27,9,31,1,6,31,35,2,35,9,39,1,39,6,43,2,9,43,47,1,47,6,51,2,51,9,55,1,5,55,59,2,59,6,63,1,9,63,67,1,67,10,71,1,71,13,75,2,13,75,79,1,6,79,83,2,9,83,87,1,87,6,91,2,10,91,95,2,13,95,99,1,9,99,103,1,5,103,107,2,9,107,111,1,111,5,115,1,115,5,119,1,10,119,123,1,13,123,127,1,2,127,131,1,131,13,0,99,2,14,0,0};

    int i = 0;
    int opcode = 0;

    // Modifications required by challenge
    a[1] = 12;
    a[2] = 2;

    while (1)
    {
        opcode = a[i];
        TRACE("At %d ", i)
        if (opcode == ADD)
        {
            TRACE("found ADD\n");
            a[DEST] = a[ARG1] + a[ARG2];
        }
        else if (opcode == MULTIPLY)
        {
            TRACE("found MULTIPLY\n");
            a[DEST] = a[ARG1] * a[ARG2];
        }
        else if (opcode == STOP)
        {
            TRACE("found STOP\n");
            break;
        }
        else
        {
            TRACE("found ERROR\n");
            break;
        }

        i += 4;
    }
    printf("a[0] = %d\n", a[0]);
}

// printf("array: ");
// for (int i = 0; i < ARRAY_SIZE; i++)
// {
//     printf("%d ", a[i]);
// }
// printf("\n");