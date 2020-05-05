#include "include.h"

#define NUM_AMPLIFIERS 5

bool all_amplifiers_halted(DATA* amplifier[])
{
    bool all_halted = true;

    for (int i = 0; i < NUM_AMPLIFIERS; i++)
    {
        if (amplifier[i]->has_halted == false)
        {
            all_halted == false;
        }
    }

    return all_halted;
}

void print_int_array(int array[], int length)
{
    printf("( ");
    for (int i = 0; i < length; i++)
    {
        printf("%d ", array[i]);
    }
    printf(")");
}

int run_amplifiers(int* current_phase_settings, DATA* amplifier[])
{
    int output = 0;

    print_int_array(current_phase_settings, NUM_AMPLIFIERS);

    // store each phase setting. This is not the same as inputting them
    for (int i = 0; i < NUM_AMPLIFIERS; i++)
    {
        amplifier[i]->phase = current_phase_settings[i];
    }

    // Give the 0th amplifier an input of 0 to kick us off
    intcode(amplifier[0],      0, &output);
    intcode(amplifier[1], output, &output);
    intcode(amplifier[2], output, &output);
    intcode(amplifier[3], output, &output);
    intcode(amplifier[4], output, &output);

    while (all_amplifiers_halted(amplifier) == false)
    {
        // run every amplifier once
        for (int i = 0; i < NUM_AMPLIFIERS; i++)
        {
            intcode(amplifier[i], output, &output);
        }
    }
    
    printf(" => %10d\n", output);

    return output;
}

int main()
{

    // int program[] = {3,8,1001,8,10,8,105,1,0,0,21,38,63,72,81,106,187,268,349,430,99999,3,9,101,5,9,9,1002,9,3,9,101,3,9,9,4,9,99,3,9,102,3,9,9,101,4,9,9,1002,9,2,9,1001,9,2,9,1002,9,4,9,4,9,99,3,9,1001,9,3,9,4,9,99,3,9,102,5,9,9,4,9,99,3,9,102,4,9,9,1001,9,2,9,1002,9,5,9,1001,9,2,9,102,3,9,9,4,9,99,3,9,1001,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,1,9,9,4,9,3,9,102,2,9,9,4,9,3,9,101,2,9,9,4,9,99,3,9,1001,9,2,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,1,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,1,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,1001,9,1,9,4,9,99,3,9,102,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,2,9,9,4,9,99,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,1,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,101,1,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,99,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,101,1,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,1,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,1001,9,1,9,4,9,3,9,102,2,9,9,4,9,3,9,101,2,9,9,4,9,99};
    // int program[] = {3,15,3,16,1002,16,10,16,1,16,15,15,4,15,99,0,0}; // example 1.1
    // int program[] = {3,23,3,24,1002,24,10,24,1002,23,-1,23,101,5,23,23,1,24,23,23,4,23,99,0,0}; // example 1.2
    // int program[] = {3,31,3,32,1002,32,10,32,1001,31,-2,31,1007,31,0,33,1002,33,7,33,1,33,31,31,1,32,31,31,4,31,99,0,0,0}; // example 1.3
    int program[] = {3,26,1001,26,-4,26,3,27,1002,27,2,27,1,27,26,27,4,27,1001,28,-1,28,1005,28,6,99,0,0,5}; // example 2.1
    int program_length = sizeof(program)/sizeof(int);

    // int phase_settings[NUM_AMPLIFIERS] = {5,6,7,8,9};
    int phase_settings[NUM_AMPLIFIERS] = {9,8,7,6,5}; // the optimum phase for 2.1

    DATA* amplifier[NUM_AMPLIFIERS];

    for (int i =0; i < NUM_AMPLIFIERS; i++)
    {
        amplifier[i] = intcode_create(program, program_length);
    }

    // permute(phase_settings, NUM_AMPLIFIERS, run_amplifiers, amplifier);

    run_amplifiers(phase_settings, amplifier);

    for (int i =0; i < NUM_AMPLIFIERS; i++)
    {
        intcode_destroy(amplifier[i]);
    }
}
