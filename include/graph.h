#ifndef GRAPH_H_
#define GRAPH_H_

#include <raylib.h>
#include <stdlib.h>

typedef struct Vert {
    Vector2 pos;
} Vert;

typedef struct VertList {
    size_t size;
    Vert **head;
} VertList;

Vert *create_vert(Vector2 pos);

#endif // GRAPH_H_
