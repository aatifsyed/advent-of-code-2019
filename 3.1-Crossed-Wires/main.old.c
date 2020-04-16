#include <stdio.h>

struct Vertex
{
    int x;
    int y;
};

struct Line
{
    struct Vertex start;
    struct Vertex end;
};

// returns the intersection point of a line (or 0,0 if no intersection.
// this is OK, since challenge ignores origin)
struct Vertex intersection(struct Line A, struct Line B)
{
    struct Vertex intersection = {0, 0};

    return intersection;
}

int main()
{
    struct Vertex vertex = {0,0};
    struct Line line = {0,0,0,0};
    vertex.x = 6;
    vertex.y = 9;
    
    printf("Line end at (%d,%d)\n", line.end.x, line.end.y);
    

}

// Notes
    // struct Line line = {vertex, {3,4}}; // line.start.x,y will forever be 0 unless mutated
    // struct Line line = {.start = {0,0},
    //                     .end = {.x = 1, .y=2}};
    
    // For intersection, I wanted to roll my own...
    // initial sketch was something like...
    // (Ax, Ay) (Bx, By)
    // (Cx, Cy) (Dx, Dy)
    // (Ax >= Cx >= Bx) ? 
    // But then we end up needing to see if AB CD are horizontal or not
    // While feasible, it's better to do something more generic