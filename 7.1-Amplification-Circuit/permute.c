#ifndef PERMUTE_C
#define PERMUTE_C

#include "include.h"
#define LIST_SIZE 4

// Implements a Johnson and Trotter algorithm as detailed on G4G

bool is_mobile(PERMUTING_INT* list, int index)
{
    int pointed_neighbour = 0;
    int value = 0;
    int neighbour_index = 0;

    if (list[index].looking_right)
    {
        neighbour_index = index + 1;
    }
    else
    {
        neighbour_index = index - 1;
    }

    if ( (neighbour_index < 0) || (neighbour_index >= LIST_SIZE) )
    {
        // we're out of bounds
        return false;
    }
    
    pointed_neighbour = list[neighbour_index].integer;
    value = list[index].integer;

    if ( value > pointed_neighbour)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// returns index of largest mobile
int largest_mobile(PERMUTING_INT* list)
{
    int index_of_largest_so_far = 0;
    int largest_so_far = 0;
    int this_value = 0;

    for (int i; i < LIST_SIZE; i++)
    {
        this_value = list[i].integer;
        largest_so_far = list[index_of_largest_so_far].integer;

        if ( is_mobile(list, i) && (this_value > largest_so_far) )
        {
            index_of_largest_so_far = i;
        }
    }
}

// not safe
void swap(PERMUTING_INT* list, int index)
{
    PERMUTING_INT swapping;
    int neighbour_index = 0;

    if (list[index].looking_right)
    {
        neighbour_index = index + 1;
    }
    else
    {
        neighbour_index = index - 1;
    }

    if ( (neighbour_index < 0) || (neighbour_index >= LIST_SIZE) )
    {
        printf("we're out of bounds\n");
    }

    swapping = list[index];
    list[index] = list[neighbour_index];
    list[neighbour_index] = swapping;
}

void flip(bool* this)
{
    if (*this == true)
    {
        *this == false;
    }
    else
    {
        *this == true;
    }
}

void flip_greater_than(PERMUTING_INT* list, int reference)
{
    int this_value = 0;

    for (int i; i < LIST_SIZE; i++)
    {
        this_value = list[i].integer;
        if ( this_value > reference )
        {
            flip(&list[i].looking_right);
        }
    }
}

bool permute_complete(PERMUTING_INT* list)
{
    bool mobile_found = false;

    for (int i; i < LIST_SIZE; i++)
    {
        if (is_mobile(list, i))
        {
            mobile_found = true;
        }
    }

    if (mobile_found)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void permute_dump(PERMUTING_INT* list)
{
    printf("( ");
    for (int i = 0; i < LIST_SIZE; i++)
    {
        printf("%d ", list[i].integer);
    }
    printf(")\n");
}

int main()
{
    PERMUTING_INT list[LIST_SIZE] = { {0, false}, {1, false}, {2, false}, {3, false} };

    permute_dump(&list);

    while (permute_complete(&list) != true)
    {
        int index_of_largest_mobile = largest_mobile(&list);
        int value_of_largest_mobile = list[index_of_largest_mobile].integer;
        swap(&list, index_of_largest_mobile);
        flip_greater_than(&list, value_of_largest_mobile);
        permute_dump(&list);
    }
}

#endif