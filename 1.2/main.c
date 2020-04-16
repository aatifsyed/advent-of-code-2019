#include <stdio.h>
#include <stdlib.h>
// #define TEST
#ifdef TEST
#define TRACE(fmt, args...) printf(fmt, ##args);
#else
#define TRACE(fmt, args...)
#endif

#define BUFF_SIZE 255

// Takes mass, divides by 3, rounds down, and subtracts two
int fuel_to_lift(int mass)
{
    TRACE("\nfuel to lift %d is ", mass);
    // divide by 3
    mass /=3;
    // subtract 2
    mass -= 2;
    TRACE("%d", mass);
    return mass;
}

// recursively calculates fuel for a module
int total_fuel_for(int mass)
{
    int fuel = 0;
    fuel = fuel_to_lift(mass);

    if (fuel <= 0)
    {
        return 0;
    }
    else
    {
        return fuel + total_fuel_for(fuel);
    }
}

int main()
{
    FILE* file_pointer = NULL;
    char buff[BUFF_SIZE];
    int running_fuel_sum = 0;
    int module_mass = 0;
    int fuel_required = 0;

    file_pointer = fopen("input", "r");
    
    while (fgets(buff, BUFF_SIZE, file_pointer))
    {
        printf("read: %s", buff);
        module_mass = strtol(buff, NULL, 10);
        printf("\tas a number: %d\n", module_mass);
        fuel_required = total_fuel_for(module_mass);
        printf("\tfuel required: %d\n", fuel_required);
        running_fuel_sum += fuel_required;
        printf("\trunning total: %d\n", running_fuel_sum);
    }
    printf("\ntotal: %d\n", running_fuel_sum);
    
    fclose(file_pointer);
}

// // test main
// int main()
// {
//     int testinput = 1969;
//     int testoutput = 0;

//     printf("testinput %d", testinput);
//     testoutput = total_fuel_for(testinput);
//     printf("\ntestoutput %d", testoutput);
//     printf("\n");
// }