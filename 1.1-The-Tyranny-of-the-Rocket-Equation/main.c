#include <stdio.h>
#include <stdlib.h>
#define BUFF_SIZE 255

// Takes mass, divides by 3, rounds down, and subtracts two
int fuel_required_for_mass(int mass) {
    // divide by 3 and round down
    mass /= 3;
    // subtract 2
    mass -= 2;
    return mass;
}

int main()
{
    FILE* file_pointer = NULL;
    char buff[BUFF_SIZE];
    int running_sum = 0;
    int current_num = 0;
    int fuel_required = 0;

    file_pointer = fopen("input", "r");
    
    while (fgets(buff, BUFF_SIZE, file_pointer))
    {
        printf("read: %s", buff);
        current_num = strtol(buff, NULL, 10);
        printf("\tas a number: %d\n", current_num);
        fuel_required = fuel_required_for_mass(current_num);
        printf("\tfuel required: %d\n", fuel_required);
        running_sum += fuel_required;
        printf("\trunning total: %d\n", running_sum);
    }
    printf("\ntotal: %d\n", running_sum);
    
    fclose(file_pointer);
}