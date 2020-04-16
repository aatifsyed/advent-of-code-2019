#include "include.h"

// Terminology:
// pointer - an integeter that refers to a position in memory
// value - the integer at a given position in memory
// index - the parameter number following the instruction. That is, pointer relative to instruction

// Dumps memory, and optionally halts
void dump(Data* data, bool halt)
{
    printf("Dumping ");
    for (int i = 0; i < data->length; i++)
    {
        printf("%3d", data->memory[i]);

        // don't add a trailing comma
        if (i != data->length -1 )
        {
            printf(",");
        }
    }
    printf("\n");

    if (halt)
    {
        printf("Halting\n");
        exit(1);
    }
}

// Rightmost two digits of current instruction
int opcode(Data* data)
{
    int instruction = 0;
    int opcode = 0;

    instruction = data->memory[data->intruction_pointer];
    opcode = instruction % 100;

    return opcode;
}

// Returns base raised to the exponent
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

// Returns mode of given parameter
int mode(Data* data, int parameter_index)
{
    int mode = -1;
    int divisor = 0;
    int quotient = 0;
    int instruction = data->memory[data->intruction_pointer];

    // Parameter modes are specified from the hundreds place.
    // (Instruction ABCDE has parameter 1 mode C, parameter 2 mode B etc)
    // So the divisor should be as follows
    // param 1 -> 100   = 10 * 10
    // param 2 -> 1000  = 10 * 100
    // param 3 -> 10000 = 10 * 1000
    divisor = 10 * _pow(10, parameter_index);

    // Chop off the irrelevant rightmost digits
    // eg. ABCDE -> ABC
    quotient = instruction/divisor;

    // Get the rightmost digit after the division
    // eg. ABC -> C
    mode = quotient % 10;

    CHECK_MODE(mode);
    return mode;
}

// Returns the value at parameter index
int immediate_mode(Data* data, int parameter_index)
{
    int parameter_pointer = 0;
    int parameter_value = 0;

    parameter_pointer = data->intruction_pointer + parameter_index;
    parameter_value = data->memory[parameter_pointer];

    return parameter_value;
}

// Returns the value pointed to by the paramter
int positional_mode(Data* data, int parameter_index)
{
    int parameter_pointer = 0;
    int parameter_value = 0;
    int value_pointed_to = 0;

    parameter_pointer = data->intruction_pointer + parameter_index;
    parameter_value = data->memory[parameter_pointer];
    value_pointed_to = data->memory[parameter_value];

    return value_pointed_to;
}

// Returns value of parameter, depending on mode
int modal(Data* data, int parameter_index)
{
    switch (mode(data, parameter_index))
    {
        case POSITION_MODE:
            return positional_mode(data, parameter_index);
            break;
        case IMMEDIATE_MODE:
            return immediate_mode(data, parameter_index);
            break;
        default:
            printf("ERROR: Invalid mode!\n");
            exit(-1);
            break;
    }
}

// Writes the given value to the given index
void write(Data* data, int value, int pointer)
{
    if (pointer >= data->length)
    {
        printf("ERROR: Tried to write out of memory");
    }
    data->memory[pointer] = value;
}

// Writes to pointer at parameter index
void write_param(Data* data, int result, int parameter_index)
{
    int parameter_value = 0;
    int target_pointer = 0;

    parameter_value = data->intruction_pointer + parameter_index;
    target_pointer = data->memory[parameter_value];
    write(data, result, target_pointer);
}

int intcode(Data* data)
{
    int result;

    while (true)
    {
        switch (opcode(data))
        {
            case ADD:
                result = modal(data, 1) + modal(data, 2);
                write_param(data, result, 3);
                data->intruction_pointer += 4;
                break;
            case MULTIPLY:
                result = modal(data, 1) * modal(data, 2);
                write_param(data, result, 3);
                data->intruction_pointer += 4;
                break;
            case INPUT:
                printf("INPUT: ");
                scanf("%d", &result);
                write_param(data, result, 1);
                data->intruction_pointer += 2;
                break;
            case OUTPUT:
                result = modal(data, 1);
                printf("OUTPUT: %d\n", result);
                data->intruction_pointer += 2;
                break;
            case JUMP_IF_TRUE:
                if (modal(data, 1) != 0)
                {
                    data->intruction_pointer = modal(data, 2);
                }
                else
                {
                    data->intruction_pointer +=3;
                }
                break;
            case JUMP_IF_FALSE:
                if (modal(data, 1) == 0)
                {
                    data->intruction_pointer = modal(data, 2);
                }
                else
                {
                    data->intruction_pointer +=3;
                }
                break;
            case LESS_THAN:
                if (modal(data, 1) < modal(data, 2))
                {
                    write_param(data, 1, 3);
                }
                else
                {
                    write_param(data, 0, 3);
                }
                data->intruction_pointer +=4;
                break;
            case EQUALS:
                if (modal(data, 1) == modal(data, 2))
                {
                    write_param(data, 1, 3);
                }
                else
                {
                    write_param(data, 0, 3);
                }
                data->intruction_pointer +=4;
                break;
            case STOP:
                printf("STOP\n");
                goto FINISH_EXECUTION;
                break;
            default:
                printf("ERROR: Unknown opcode!\n");
                goto FINISH_EXECUTION;
                break;
        }
    }
    FINISH_EXECUTION:
    return data->memory[0];
}

int main()
{
    Data data;
    int output = 0;

    int memory[] = {3,225,1,225,6,6,1100,1,238,225,104,0,1102,91,92,225,1102,85,13,225,1,47,17,224,101,-176,224,224,4,224,1002,223,8,223,1001,224,7,224,1,223,224,223,1102,79,43,225,1102,91,79,225,1101,94,61,225,1002,99,42,224,1001,224,-1890,224,4,224,1002,223,8,223,1001,224,6,224,1,224,223,223,102,77,52,224,1001,224,-4697,224,4,224,102,8,223,223,1001,224,7,224,1,224,223,223,1101,45,47,225,1001,43,93,224,1001,224,-172,224,4,224,102,8,223,223,1001,224,1,224,1,224,223,223,1102,53,88,225,1101,64,75,225,2,14,129,224,101,-5888,224,224,4,224,102,8,223,223,101,6,224,224,1,223,224,223,101,60,126,224,101,-148,224,224,4,224,1002,223,8,223,1001,224,2,224,1,224,223,223,1102,82,56,224,1001,224,-4592,224,4,224,1002,223,8,223,101,4,224,224,1,224,223,223,1101,22,82,224,1001,224,-104,224,4,224,1002,223,8,223,101,4,224,224,1,223,224,223,4,223,99,0,0,0,677,0,0,0,0,0,0,0,0,0,0,0,1105,0,99999,1105,227,247,1105,1,99999,1005,227,99999,1005,0,256,1105,1,99999,1106,227,99999,1106,0,265,1105,1,99999,1006,0,99999,1006,227,274,1105,1,99999,1105,1,280,1105,1,99999,1,225,225,225,1101,294,0,0,105,1,0,1105,1,99999,1106,0,300,1105,1,99999,1,225,225,225,1101,314,0,0,106,0,0,1105,1,99999,8,226,677,224,102,2,223,223,1005,224,329,1001,223,1,223,1007,226,226,224,1002,223,2,223,1006,224,344,101,1,223,223,108,226,226,224,1002,223,2,223,1006,224,359,1001,223,1,223,107,226,677,224,102,2,223,223,1006,224,374,101,1,223,223,8,677,677,224,102,2,223,223,1006,224,389,1001,223,1,223,1008,226,677,224,1002,223,2,223,1006,224,404,101,1,223,223,7,677,677,224,1002,223,2,223,1005,224,419,101,1,223,223,1108,226,677,224,1002,223,2,223,1005,224,434,101,1,223,223,1108,226,226,224,102,2,223,223,1005,224,449,1001,223,1,223,107,226,226,224,102,2,223,223,1005,224,464,101,1,223,223,1007,677,677,224,102,2,223,223,1006,224,479,101,1,223,223,1007,226,677,224,102,2,223,223,1005,224,494,1001,223,1,223,1008,226,226,224,1002,223,2,223,1005,224,509,1001,223,1,223,1108,677,226,224,1002,223,2,223,1006,224,524,1001,223,1,223,108,677,677,224,1002,223,2,223,1005,224,539,101,1,223,223,108,226,677,224,1002,223,2,223,1005,224,554,101,1,223,223,1008,677,677,224,1002,223,2,223,1006,224,569,1001,223,1,223,1107,677,677,224,102,2,223,223,1005,224,584,1001,223,1,223,7,677,226,224,102,2,223,223,1005,224,599,1001,223,1,223,8,677,226,224,1002,223,2,223,1005,224,614,1001,223,1,223,7,226,677,224,1002,223,2,223,1006,224,629,101,1,223,223,1107,677,226,224,1002,223,2,223,1005,224,644,1001,223,1,223,1107,226,677,224,102,2,223,223,1006,224,659,1001,223,1,223,107,677,677,224,1002,223,2,223,1005,224,674,101,1,223,223,4,223,99,226};
    int length = sizeof(memory)/sizeof(int);

    data.memory = &memory[0];
    data.length = length;
    data.intruction_pointer = 0;

    output = intcode(&data);
}
