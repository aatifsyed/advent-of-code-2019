#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#define WIDTH  25
#define HEIGHT 6

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

void print_layer_info(LAYER_INFO* layer_info)
{
    printf("%6d zeroes\n", layer_info->zeroes);
    printf("%6d ones\n", layer_info->ones);
    printf("%6d twos\n", layer_info->twos);
}

int get_file_length()
{
    int length = 0;
    FILE* file = fopen("input", "r");
    while ( fgetc(file) != EOF)
    {
        length++;
    }
    perror("b");
    fclose(file);
    return length;
}

int main()
{
    int chars_per_layer = WIDTH * HEIGHT;
    int file_length = get_file_length();
    int num_layers = file_length/chars_per_layer;
    LAYER_INFO layers[num_layers];

    FILE* input_file = fopen("input", "r");
    perror("input");
    for (int layer_index; layer_index < num_layers; layer_index++)
    {
        for (int character_count; character_count < chars_per_layer; character_count++)
        {
            char current_character = fgetc(input_file);
            switch (current_character)
            {
                case '0':
                    layers[layer_index].zeroes++;
                    break;
                case '1':
                    layers[layer_index].ones++;
                    break;
                case '2':
                    layers[layer_index].twos++;
                    break;
                default:
                    printf("Unexpected character: %c", current_character);
            }
        }
    }
    // assert(fgetc(input_file) == EOF);
    fclose(input_file);

    int index_with_fewest_zeroes = 0;
    int fewest_zeroes_so_far = layers[0].zeroes;

    for (int layer_index; layer_index < num_layers; layer_index++)
    {
        if (layers[layer_index].zeroes < fewest_zeroes_so_far)
        {
            index_with_fewest_zeroes = layer_index;
            fewest_zeroes_so_far = layers[layer_index].zeroes;
        }
    }

    int checksum = layers[index_with_fewest_zeroes].ones * layers[index_with_fewest_zeroes].twos;

    printf("Checksum: %d\n", checksum);
    
}