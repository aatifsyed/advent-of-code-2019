#include <stdio.h>
#include <stdlib.h>

typedef struct layer_info
{
    int zeroes;
    int ones;
    int twos;
    struct layer_info* tail;
} LAYER_INFO;

void layer_info_new_head(LAYER_INFO** head)
{
    LAYER_INFO* new_layer_info = (LAYER_INFO*) malloc(sizeof(LAYER_INFO));
    new_layer_info->zeroes = 0;
    new_layer_info->ones = 0;
    new_layer_info->twos = 0;
    new_layer_info->tail = *head;
    *head = new_layer_info;
}

void reset_counters(int* zeroes, int* ones, int* twos)
{
    *zeroes = 0;
    *ones = 0;
    *twos = 0;
}

void dump_and_reset(int* zeroes, int* ones, int* twos)
{
    printf("%d zeroes\n", *zeroes);
    printf("%d ones\n", *ones);
    printf("%d twos\n", *twos);
    printf("\n");
    reset_counters(zeroes, ones, twos);
}

int main()
{
    FILE* file = NULL;
    LAYER_INFO* head = NULL;
    char current_char = '\0';
    int current_zeroes = 0;
    int current_ones = 0;
    int current_twos = 0;
    int num_chars = 0;

    file = fopen("input", "r");
    printf("file at %p\n", file);

    while ( (current_char = fgetc(file)) != EOF )
    {
        num_chars++;

        // printf("%c", current_char);
        switch (current_char)
        {
            case '0':
                current_zeroes++;
                break;
            case '1':
                current_ones++;
                break;
            case '2':
                current_twos++;
                break;
            default:
                printf("unexpected char: %c\n", current_char);
                break;
        }

        if (num_chars == (25 * 6))
        {
            num_chars = 0;
            layer_info_new_head(&head);
            printf("new head\n");
            head->zeroes = current_zeroes;
            head->ones = current_ones;
            head->twos = current_twos;

            reset_counters(&current_zeroes, &current_ones, &current_twos);
        }
    }
    printf("closing file...\n");
    fclose(file);
    printf("closed file\n");

    LAYER_INFO* current = head;
    LAYER_INFO* fewest_zeroes = head;
    int fewest_zeroes_so_far = head->zeroes;

    while (current != NULL)
    {
        printf("looping through\n");
        if (current->zeroes < fewest_zeroes_so_far)
        {
            fewest_zeroes_so_far = current->zeroes;
            fewest_zeroes = current;
        }

        current = current->tail;
    }
    printf("looped through\n");


    int answer = fewest_zeroes->ones * fewest_zeroes->zeroes;

    printf("%d\n", answer);
}
