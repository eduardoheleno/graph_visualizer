#ifndef GRAPH_H_
#define GRAPH_H_

#include <raylib.h>
#include <stdlib.h>

#define DEFAULT_VERT_RADIUS 20

typedef struct Vert {
    Vector2 pos;
    size_t size;
    struct Edge **edges;
} Vert;

typedef struct Edge {
    size_t weight;
    Vert *dest_vert;
    Rectangle rec;
    float rot;
} Edge;

typedef struct VertList {
    size_t size;
    Vert **verts;
} VertList;

Vert *create_vert(Vector2 pos);
Edge *create_edge(Vert *dest, size_t weight, Rectangle rec, float rot);
void set_edge(Vert *orig, Vert *dest, size_t weight,
    Rectangle *rec, float *rot);

#endif // GRAPH_H_
