#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define BETWEEN(START, TEST, END) ((START >= TEST && TEST >= END) ||      \
                                   (START <= TEST && TEST <= END))

enum Orientation {
    horizontal, // invariant is y
    vertical // invariant is x
};

struct Segment {
    enum Orientation orientation;
    int invariant; // location
    int start; // co-ordinate
    int end; // co-ordinate
    struct Segment* next; // this is a linked list
};

struct Vertex {
    int x;
    int y;
};

int manhattan_to_intersection(struct Segment A, struct Segment B) {
    // discard parallel lines
    if (A.orientation == B.orientation) {
        return 0;
    }
    
    // if lines intersect, return manhattan distance from origin
    if (BETWEEN(A.start, B.invariant, A.end) && BETWEEN(B.start, A.invariant, B.end)) {
        return B.invariant + A.invariant;
    }
    else {
        return 0;
    }
}

struct Segment* parse_input() {
    enum Orientation orientation;
    enum {positive = +1, negative = -1} direction;

    int magnitude = 0;
    bool end_of_value = false;
    bool end_of_line = false;

    struct Segment* first;
    struct Segment* current;
    struct Vertex cursor;

    char c;
    FILE* input = NULL;
    // newline terminate file
    input = fopen("testinput", "r");

    while ( (c = fgetc(input)) != EOF) {
        switch (c) {
        case 'U':
            orientation = vertical;
            direction = positive;
            break;
        case 'D':
            orientation = vertical;
            direction = negative;
            break;
        case 'R':
            orientation = horizontal;
            direction = positive;
            break;
        case 'L':
            orientation = horizontal;
            direction = negative;
            break;
        case '\n':
            end_of_line = true;
        case ',':
            // printf("COMMA");
            end_of_value = true;
            break;
        default:
            if (BETWEEN('0', c, '9')) {
                magnitude *= 10; // shift digits to the left
                magnitude += c - '0'; // add the newfound digit
            }
            else {
                printf("Unexpected character\n");
            }
            break;
        }

        if (end_of_value) {
            current = malloc(sizeof(struct Segment));
            if (orientation == vertical) {
                current->start = cursor.y;
                current->end = cursor.y + direction * magnitude;
                current->orientation = orientation;
                current->invariant = cursor.x;
            }
            if (orientation == horizontal) {
                current->start = cursor.x;
                current->end = cursor.x + direction * magnitude;
                current->orientation = orientation;
                current->invariant = cursor.y;
            }
            
            // now reset counters
            end_of_value = 0;
            magnitude = 0;
        }
    }

}

int main() {
    parse_input();
    
}