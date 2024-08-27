#include "graph.h"

Vert *create_vert(Vector2 pos)
{
    Vert *v = malloc(sizeof(Vert));
    v->pos = pos;
    v->edges = NULL;

    return v;
}

Edge *create_edge(Vert *dest, size_t weight, Rectangle rec, float rot)
{
    Edge *e = malloc(sizeof(Edge));
    e->dest_vert = dest;
    e->weight = weight;
    e->rec = rec;
    e->rot = rot;

    return e;
}

void set_edge(Vert *orig, Vert *dest, size_t weight, Rectangle *rec, float *rot)
{
    Edge *e = create_edge(dest, weight, *rec, *rot);
    orig->size++;

    orig->edges = realloc(orig->edges, sizeof(Edge*) * orig->size);
    orig->edges[orig->size - 1] = e;
}
