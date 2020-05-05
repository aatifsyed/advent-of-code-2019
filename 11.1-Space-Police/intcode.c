#ifndef INTCODE_C
#define INTCODE_C

#include "include.h"

// Terminology:
// pointer - an integer that refers to a position in memory
// value - the integer at a given position in memory
// index - the parameter number following the instruction. That is, pointer relative to instruction

// Dumps memory, and optionally halts
void dump(DATA* data, bool halt)
{
    int pointer = 0;

    printf("Dumping ");
    for (pointer = 0; pointer < data->length; pointer++)
    {
        printf("%ld", data->memory[pointer]);

        // don't add a trailing comma
        if (pointer != data->length -1 )
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
int opcode(DATA* data)
{
    int instruction = 0;
    int opcode = 0;

    instruction = data->memory[data->intruction_pointer];
    opcode = instruction % 100;

    return opcode;
}

// Returns base raised to the exponent
int int_pow(int base, int exponent)
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
int mode(DATA* data, int parameter_index)
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
    divisor = 10 * int_pow(10, parameter_index);

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
long int immediate_mode(DATA* data, int parameter_index)
{
    int parameter_pointer = 0;
    long int parameter_value = 0;

    parameter_pointer = data->intruction_pointer + parameter_index;
    parameter_value = data->memory[parameter_pointer];

    return parameter_value;
}

// Returns the value pointed to by the paramter
long int positional_mode(DATA* data, int parameter_index)
{
    int parameter_pointer = 0;
    long int parameter_value = 0;
    long int value_pointed_to = 0;

    parameter_pointer = data->intruction_pointer + parameter_index;
    parameter_value = data->memory[parameter_pointer];
    value_pointed_to = data->memory[parameter_value];

    return value_pointed_to;
}

long int relative_mode(DATA* data, int parameter_index)
{
    int parameter_pointer = 0;
    int shifted_index = 0;
    long int parameter_value = 0;
    long int value_pointed_to = 0;
    int relative_base = data->relative_base;

    parameter_pointer = data->intruction_pointer + parameter_index;
    parameter_value = data->memory[parameter_pointer];
    shifted_index = parameter_value + relative_base;
    value_pointed_to = data->memory[shifted_index];

    return value_pointed_to;
}

// Returns value of parameter, depending on mode
long int modal(DATA* data, int parameter_index)
{
    switch (mode(data, parameter_index))
    {
        case POSITION_MODE:
            return positional_mode(data, parameter_index);
            break;
        case IMMEDIATE_MODE:
            return immediate_mode(data, parameter_index);
            break;
        case RELATIVE_MODE:
            return relative_mode(data, parameter_index);
            break;
        default:
            printf("ERROR: Invalid mode!\n");
            exit(EXIT_FAILURE);
            break;
    }
}

// Writes the given value to the given pointer
void write(DATA* data, long int value, int pointer)
{
    if (pointer >= data->length)
    {
        printf("ERROR: Tried to write out of memory");
        exit(-1);
    }
    data->memory[pointer] = value;
}

void write_modal(DATA* data, long int result, int parameter_index)
{
    int pointer_of_param = 0;
    long int value_of_param = 0;
    int pointer_of_destination = 0;
    int shifted_address_of_param = 0;

    switch (mode(data, parameter_index))
    {
        case POSITION_MODE:
            pointer_of_param = data->intruction_pointer + parameter_index;
            pointer_of_destination = (int) data->memory[pointer_of_param];
            write(data, result, pointer_of_destination);
            break;
        case RELATIVE_MODE:
            pointer_of_param = data->intruction_pointer + parameter_index;
            value_of_param = data->memory[pointer_of_param];
            pointer_of_destination = value_of_param + data->relative_base;
            write(data, result, pointer_of_destination);
            break;
        default:
            printf("ERROR: not a valid writing mode!\n");
            exit(EXIT_FAILURE);
            break;
    }
}

// Writes to pointer at parameter index
void write_param(DATA* data, long int result, int parameter_index)
{
    write_modal(data, result, parameter_index);
}

void load_from_backup(DATA* data)
{
    memcpy(data->memory, data->backup, data->length * sizeof(data->memory[0]));
}

void intcode_reset(DATA* data)
{
    load_from_backup(data);
    data->intruction_pointer = 0;
    data->relative_base = 0;
}

// Dynamically allocates a DATA struct for an intcode computer
DATA* intcode_create(long int* memory_template, int length)
{
    DATA* data = malloc(sizeof(DATA));

    long int* backup = malloc(sizeof(memory_template[0]) * length);
    long int* memory = malloc(sizeof(memory_template[0]) * length);
    
    data->backup = backup;
    data->memory = memory;
    data->length = length;

    memcpy(data->backup, memory_template, length * sizeof(memory_template[0]));

    intcode_reset(data);

    return data;
}

void intcode_destroy(DATA* data)
{
    free(data->backup);
    free(data->memory);
    free(data);
}

int intcode(DATA* data)
{
    long int result;

    while (true)
    {
        switch (opcode(data))
        {
            case ADD:
                result = modal(data, 1) + modal(data, 2);
                write_modal(data, result, 3);
                data->intruction_pointer += 4;
                break;
            case MULTIPLY:
                result = modal(data, 1) * modal(data, 2);
                write_modal(data, result, 3);
                data->intruction_pointer += 4;
                break;
            case INPUT:
                printf("Input : ");
                scanf("%ld", &result);
                write_modal(data, result, 1);
                data->intruction_pointer += 2;
                break;
            case OUTPUT:
                result = modal(data, 1);
                printf("Output: %ld\n", result);
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
                    write_modal(data, 1, 3);
                }
                else
                {
                    write_modal(data, 0, 3);
                }
                data->intruction_pointer +=4;
                break;
            case EQUALS:
                if (modal(data, 1) == modal(data, 2))
                {
                    write_modal(data, 1, 3);
                }
                else
                {
                    write_modal(data, 0, 3);
                }
                data->intruction_pointer +=4;
                break;
            case RELATIVE_BASE_OFFSET:
                result = modal(data, 1);
                data->relative_base += result;
                data->intruction_pointer +=2;
                break;
            case STOP:
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

#endif