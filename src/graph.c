#include "graph.h"

Vert *create_vert(Vector2 pos)
{
    Vert *v = malloc(sizeof(Vert));
    v->pos = pos;

    return v;
}
