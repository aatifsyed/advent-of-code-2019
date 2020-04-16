#include <stdio.h>

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

int square(int base)
{
    return _pow(base, 2);
}

int cube(int base)
{
    return _pow(base, 3);
}

// int (*function)(int) return_function()
// {

// }

int main()
{
    int (*function)(int);

    if (0)
    {
        function = square;
    }
    else
    {
        function = cube;
    }
    
    printf("%d\n", function(2));
}