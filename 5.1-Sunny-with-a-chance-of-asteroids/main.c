#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TRACE(fmt, args...) //printf(fmt, ##args)

#define ADD      1
#define MULTIPLY 2
#define INPUT    3
#define OUTPUT   4
#define JUMP_IF_TRUE  5
#define JUMP_IF_FALSE 6
#define LESS_THAN     7
#define EQUALS        8
#define STOP          99

#define MODAL(X)               modal(instruction, X, memory, instruction_pointer)
#define PARAMETER(param_num)   memory[instruction_pointer + param_num]

#define POSITION_MODE  0
#define IMMEDIATE_MODE 1

#define POSITION(X)    memory[X]
#define IMMEDIATE(X)   X

void dump(int memory[], int length, bool halt)
{
    TRACE("dump(%p, %d) {\n", memory, length);
    printf("\t");
    for (int i = 0; i < length; i++)
    {
        printf("%d", memory[i]);
        if (i != length -1 )
        {
            printf(",");
        }
    }
    printf("\n");
    TRACE("dump }\n");
    if (halt)
    {
        printf("halting\n");
        exit(1);
    }
}

int get_opcode(int instruction)
{
    TRACE("opcode(%d) {\n", instruction);
    int opcode = instruction % 100;
    TRACE("opcode:%d }\n",opcode);
    return opcode;
}

int _pow(int base, int exponent)
{
    int i = 0;
    int result = 1;
    for (i = 0; i < exponent; i++)
    {
        result *= base;
    }
    return result;
}

int mode(int instruction, int parameter_number)
{
    TRACE("mode(%d, %d) {\n", instruction, parameter_number);
    int mode = -1;
    int divisor = 0;
    int quotient = 0;

    // parameter modes are specified from the hundreds place.
    // (instruction ABCDE has parameter 1 mode C, parameter 2 mode B etc)
    // so the divisor should be as follows
    // param 1 -> 100   = 10 * 10
    // param 2 -> 1000  = 10 * 100
    // param 3 -> 10000 = 10 * 1000
    divisor = 10 * _pow(10, parameter_number);

    // chop off the irrelevant rightmost digits
    // eg. ABCDE -> ABC
    quotient = instruction/divisor;

    // get the rightmost digit after the division
    // eg. ABC -> C
    mode = quotient % 10;

    TRACE("mode:%d }\n",mode);
    return mode;
}

// returns either value or position of parameter, depending on mode
int modal(int instruction, int parameter_number, int memory[], int instruction_pointer)
{
    int parameter_value = 0;
    int return_value = 0;

    parameter_value = memory[instruction_pointer + parameter_number];

    if (mode(instruction, parameter_number) == POSITION_MODE)
    {
        return_value = memory[parameter_value];
    }
    else if (mode(instruction, parameter_number) == IMMEDIATE_MODE)
    {
        return_value = parameter_value;
    }
    else
    {
        printf("invalid mode\n");
    }
    return return_value;
}

int intcode()
{
    TRACE("intcode {\n");
    // int memory[] = {3,225,1,225,6,6,1100,1,238,225,104,0,1102,91,92,225,1102,85,13,225,1,47,17,224,101,-176,224,224,4,224,1002,223,8,223,1001,224,7,224,1,223,224,223,1102,79,43,225,1102,91,79,225,1101,94,61,225,1002,99,42,224,1001,224,-1890,224,4,224,1002,223,8,223,1001,224,6,224,1,224,223,223,102,77,52,224,1001,224,-4697,224,4,224,102,8,223,223,1001,224,7,224,1,224,223,223,1101,45,47,225,1001,43,93,224,1001,224,-172,224,4,224,102,8,223,223,1001,224,1,224,1,224,223,223,1102,53,88,225,1101,64,75,225,2,14,129,224,101,-5888,224,224,4,224,102,8,223,223,101,6,224,224,1,223,224,223,101,60,126,224,101,-148,224,224,4,224,1002,223,8,223,1001,224,2,224,1,224,223,223,1102,82,56,224,1001,224,-4592,224,4,224,1002,223,8,223,101,4,224,224,1,224,223,223,1101,22,82,224,1001,224,-104,224,4,224,1002,223,8,223,101,4,224,224,1,223,224,223,4,223,99,0,0,0,677,0,0,0,0,0,0,0,0,0,0,0,1105,0,99999,1105,227,247,1105,1,99999,1005,227,99999,1005,0,256,1105,1,99999,1106,227,99999,1106,0,265,1105,1,99999,1006,0,99999,1006,227,274,1105,1,99999,1105,1,280,1105,1,99999,1,225,225,225,1101,294,0,0,105,1,0,1105,1,99999,1106,0,300,1105,1,99999,1,225,225,225,1101,314,0,0,106,0,0,1105,1,99999,8,226,677,224,102,2,223,223,1005,224,329,1001,223,1,223,1007,226,226,224,1002,223,2,223,1006,224,344,101,1,223,223,108,226,226,224,1002,223,2,223,1006,224,359,1001,223,1,223,107,226,677,224,102,2,223,223,1006,224,374,101,1,223,223,8,677,677,224,102,2,223,223,1006,224,389,1001,223,1,223,1008,226,677,224,1002,223,2,223,1006,224,404,101,1,223,223,7,677,677,224,1002,223,2,223,1005,224,419,101,1,223,223,1108,226,677,224,1002,223,2,223,1005,224,434,101,1,223,223,1108,226,226,224,102,2,223,223,1005,224,449,1001,223,1,223,107,226,226,224,102,2,223,223,1005,224,464,101,1,223,223,1007,677,677,224,102,2,223,223,1006,224,479,101,1,223,223,1007,226,677,224,102,2,223,223,1005,224,494,1001,223,1,223,1008,226,226,224,1002,223,2,223,1005,224,509,1001,223,1,223,1108,677,226,224,1002,223,2,223,1006,224,524,1001,223,1,223,108,677,677,224,1002,223,2,223,1005,224,539,101,1,223,223,108,226,677,224,1002,223,2,223,1005,224,554,101,1,223,223,1008,677,677,224,1002,223,2,223,1006,224,569,1001,223,1,223,1107,677,677,224,102,2,223,223,1005,224,584,1001,223,1,223,7,677,226,224,102,2,223,223,1005,224,599,1001,223,1,223,8,677,226,224,1002,223,2,223,1005,224,614,1001,223,1,223,7,226,677,224,1002,223,2,223,1006,224,629,101,1,223,223,1107,677,226,224,1002,223,2,223,1005,224,644,1001,223,1,223,1107,226,677,224,102,2,223,223,1006,224,659,1001,223,1,223,107,677,677,224,1002,223,2,223,1005,224,674,101,1,223,223,4,223,99,226};
    int memory[] = {3,9,8,9,10,9,4,9,99,-1,8};
    int length = sizeof(memory)/sizeof(int);
    int instruction_pointer = 0;
    int opcode = 0;
    int instruction = 0;
    int io = 0;

    while (1)
    {
        instruction = memory[instruction_pointer];
        opcode = get_opcode(instruction);
        TRACE("\tAt %d ", instruction_pointer);
        if (opcode == ADD)
        {
            TRACE("found ADD\n");
            instruction_pointer += 4;
            POSITION(PARAMETER(3)) = MODAL(1) + MODAL(2);
        }
        else if (opcode == MULTIPLY)
        {
            TRACE("found MULTIPLY\n");
            instruction_pointer += 4;
            POSITION(PARAMETER(3)) = MODAL(1) * MODAL(2);
        }
        else if (opcode == INPUT)
        {
            TRACE("found INPUT\n");
            instruction_pointer += 2;
            printf("Enter input: ");
            scanf("%d", &io);
            POSITION(PARAMETER(1)) = io;
        }
        else if (opcode == OUTPUT)
        {
            TRACE("found OUTPUT\n");
            instruction_pointer += 2;
            io = MODAL(1);
            printf("output: %d\n", io);
        }
        else if (opcode == JUMP_IF_TRUE)
        {
            TRACE("found JUMP_IF_TRUE\n");
            if (MODAL(1) != 0)
            {
                instruction_pointer = MODAL(2);
            }
            else
            {
                instruction_pointer +=3;
            }
        }
        else if (opcode == JUMP_IF_FALSE)
        {
            TRACE("found JUMP_IF_FALSE\n");
            if (MODAL(1) == 0)
            {
                instruction_pointer = MODAL(2);
            }
            else
            {
                instruction_pointer +=3;
            }
        }
        else if (opcode == LESS_THAN)
        {
            TRACE("found LESS_THAN\n");
            if (MODAL(1) < MODAL(2))
            {
                POSITION(PARAMETER(3)) = 1;
            }
            else
            {
                POSITION(PARAMETER(3)) = 0;
            }
            instruction_pointer += 4;
        }
        else if (opcode == EQUALS)
        {
            TRACE("found EQUALS\n");
            if (MODAL(1) == MODAL(2))
            {
                POSITION(PARAMETER(3)) = 1;
            }
            else
            {
                POSITION(PARAMETER(3)) = 0;
            }
            instruction_pointer += 4;
        }
        else if (opcode == STOP)
        {
            TRACE("found STOP\n");
            break;
        }
        else
        {
            TRACE("ERROR\n");
            printf("\nERROR!\n");
            dump(memory, length, false);
            break;
        }

    }
    TRACE("intcode:%d }\n", memory[0]);
    return memory[0];
}

int main()
{
    TRACE("main {\n");

    intcode();

    TRACE("main }\n");
}
