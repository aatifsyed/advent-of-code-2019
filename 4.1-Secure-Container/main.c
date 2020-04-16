#include <stdio.h>
#include <stdbool.h>

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

// Returns number in column of number specified by index, where 1's column is index 0
int get_digit(int number, int index)
{   
    int divisor = 0;
    int quotient = 0;
    int digit = 0;

    // Divide, shifting number to the right.
    divisor = _pow(10, index);
    quotient = number/divisor;

    // Ignore digits to left.
    digit = quotient % 10;
    return digit;
}

bool no_more_than_two_repeating_digits(int input)
{
    int digit_index = 0;
    int right_digit = 0;
    int middle_digit = 0;
    int left_digit = 0;
    int last_matched_digit = -1;
    bool condition = false;

    for(digit_index = 0; digit_index < 4; digit_index++)
    {
        right_digit = get_digit(input, digit_index);
        middle_digit = get_digit(input, digit_index + 1);
        left_digit = get_digit(input, digit_index + 2);
        if (left_digit == middle_digit && middle_digit != right_digit)
        {
            condition = true;
        }
    }
    return false;
}

bool digits_increase_left_to_right(int input)
{
    int digit_index = 0;
    int right_digit = 0;
    int left_digit = 0;
    bool condition = true;

    for(digit_index = 0; digit_index < 5; digit_index++)
    {
        right_digit = get_digit(input, digit_index);
        left_digit = get_digit(input, digit_index + 1);
        if (right_digit < left_digit)
        {
            condition = false;
        }
    }
    return condition;
}

bool two_adjacent_digits_are_same(int input)
{
    int digit_index = 0;
    int right_digit = 0;
    int left_digit = 0;
    bool condition = false;

    for(digit_index = 0; digit_index < 5; digit_index++)
    {
        right_digit = get_digit(input, digit_index);
        left_digit = get_digit(input, digit_index + 1);
        if (right_digit == left_digit)
        {
            condition = true;
        }
    }
    return condition;
}

int main()
{
    int i = 111122;
    int count = 0;

    // for( i = 245182; i <= 790572; i++)
    {
        if(two_adjacent_digits_are_same(i) && digits_increase_left_to_right(i) && no_more_than_two_repeating_digits(i))
        {
            count++;
        }
    }
    printf("%d\n", count);
}