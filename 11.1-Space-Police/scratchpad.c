#include "include.h"
  
int main() 
{
    printf("int: %ld\n", sizeof(int));
    printf("long int: %ld\n", sizeof(long int));
    long int i = - 1125899906842624;
    printf("stored\n-1125899906842624 as:\n%ld\n", i);
}