#include <stdio.h>
#include <stdlib.h>
#define TRACE(fmt, args...)
// printf(fmt, ##args);
#define ADD      1
#define MULTIPLY 2
#define STOP     99
#define PARAMETER(X)    memory[instruction_pointer + X]

int intcode(int noun, int verb)
{
    int memory[] = {1,0,0,3,1,1,2,3,1,3,4,3,1,5,0,3,2,13,1,19,1,19,9,23,1,
                    5,23,27,1,27,9,31,1,6,31,35,2,35,9,39,1,39,6,43,2,9,43,
                    47,1,47,6,51,2,51,9,55,1,5,55,59,2,59,6,63,1,9,63,67,1,
                    67,10,71,1,71,13,75,2,13,75,79,1,6,79,83,2,9,83,87,1,
                    87,6,91,2,10,91,95,2,13,95,99,1,9,99,103,1,5,103,107,2,
                    9,107,111,1,111,5,115,1,115,5,119,1,10,119,123,1,13,
                    123,127,1,2,127,131,1,131,13,0,99,2,14,0,0};
    int instruction_pointer = 0;
    int values_per_instruction = 0;
    int opcode = 0;

    memory[1] = noun;
    memory[2] = verb;

    while (1)
    {
        opcode = memory[instruction_pointer];
        TRACE("At %d ", instruction_pointer)
        if (opcode == ADD)
        {
            TRACE("found ADD\n");
            values_per_instruction = 4;
            memory[PARAMETER(3)] = memory[PARAMETER(1)] + memory[PARAMETER(2)];
        }
        else if (opcode == MULTIPLY)
        {
            TRACE("found MULTIPLY\n");
            values_per_instruction = 4;
            memory[PARAMETER(3)] = memory[PARAMETER(1)] * memory[PARAMETER(2)];
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

        instruction_pointer += values_per_instruction;
    }
    return memory[0];
}

int main()
{
    int magic_noun;
    int magic_verb;
    int result;

    for (int noun = 0; noun < 99; noun++)
    {
        for (int verb = 0; verb < 99; verb++)
        {
            if (intcode(noun, verb) == 19690720)
            {
                magic_noun = noun;
                magic_verb = verb;
                goto EXIT_LABEL;
            }
        }
    }

    EXIT_LABEL:
    result = 100 * magic_noun + magic_verb;
    printf("%d\n", result);
}
