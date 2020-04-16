#include <stdio.h>
#include <stdlib.h>
#define BUFF_SIZE 255

int main()
{
    FILE* fptr;
    char buff[BUFF_SIZE];

    fptr = fopen("input", "r");
    
    while (fgets(buff, BUFF_SIZE, fptr))
    {
        printf("read: %s", buff);
    }
    printf("\n");
    
    fclose(fptr);
}