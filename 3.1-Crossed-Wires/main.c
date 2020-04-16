#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TRACE(fmt, args...) printf(fmt, ##args)
#define BETWEEN(START, TEST, END) ((START >= TEST && TEST >= END) ||      \
                                   (START <= TEST && TEST <= END))

// Vertices are actually unneeded in this problem. Using as a intermediary
// makes this more extensible and comprehensible.
typedef struct Vertex {
    int x;
    int y;
    struct Vertex* next;
} Vertex;

typedef enum {x,y} Direction;
typedef enum {negative=-1, positive=+1} Sign;

void print_list(Vertex* head_vertex) {
    Vertex* current_vertex = head_vertex;
    while (current_vertex != NULL)
    {
        printf("(%4d, %4d)\n", current_vertex->x, current_vertex->y);
        current_vertex = current_vertex->next;
    }
}

void new_vertex_to_list(Vertex* cursor, Vertex** head_vertex, 
                       Direction direction, Sign sign, int magnitude){
    Vertex* new_vertex = malloc(sizeof(Vertex));
    new_vertex->next = *head_vertex;
    *head_vertex = new_vertex;
    // TRACE("\tCursor IN:  (%d, %d)\n", cursor->x, cursor->y);
    if (direction == x) {
        cursor->x += sign * magnitude;
        new_vertex->x = cursor->x;
        new_vertex->y = cursor->y;
    }
    if (direction == y) {
        cursor->y += sign * magnitude;
        new_vertex->x = cursor->x;
        new_vertex->y = cursor->y;
    }
    // TRACE("\tCursor OUT: (%d, %d)\n", cursor->x, cursor->y);
}

Vertex* file_to_vertices(Vertex** first_head, Vertex** second_head) {
    Vertex cursor = {0, 0, NULL};
    Vertex* current_head = *first_head;

    Direction direction;
    Sign sign;
    int magnitude = 0;

    bool end_of_cell = false;
    bool end_of_first = false;
    char c;
    FILE* input = fopen("testinput", "r");
    
    while ( (c = fgetc(input)) != EOF) {
        switch (c) {
            case 'U':
                direction = y;
                sign = positive;
                break;
            case 'D':
                direction = y;
                sign = negative;
                break;
            case 'R':
                direction = x;
                sign = positive;
                break;
            case 'L':
                direction = x;
                sign = negative;
                break;
            case '\n':
                end_of_first = true;
            case ',':
                end_of_cell = true;
                break;
            default:
                break;
        }
        
        if (BETWEEN('0', c, '9')) {
            magnitude *= 10; // shift digits to the left
            magnitude += c - '0'; // add the newfound digit
        }
        
        if (end_of_cell) {
            TRACE("Direction: %4d, Sign: %4d, Magnitude: %4d\n", direction, sign, magnitude);
            new_vertex_to_list(&cursor, &current_head, direction, sign, magnitude);
            
            magnitude = 0;
            end_of_cell = false;
        }

        if (end_of_first) {
            TRACE("End of first\n");
            end_of_first = false;
            *first_head = current_head;
            current_head = *second_head;
            cursor.x = cursor.y = 0;
        }
    }
    *second_head = current_head;
}

int main() {
    Vertex* first_head = NULL;
    Vertex* second_head = NULL;
    file_to_vertices(&first_head, &second_head);
    printf("First list:\n");
    print_list(first_head);

    printf("Second list:\n");
    print_list(second_head);
}