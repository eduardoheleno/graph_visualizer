#include "graph.h"
#include <raylib.h>

Vert *create_vert(Vector2 pos, unsigned int index)
{
    Vert *v = malloc(sizeof(Vert));
    v->pos = pos;
    v->is_selected = false;
    v->edges = NULL;
    v->index = index;

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
    Edge *e1 = create_edge(dest, weight, *rec, *rot);
    Edge *e2 = create_edge(orig, weight, *rec, *rot);

    orig->size++;
    orig->edges = realloc(orig->edges, sizeof(Edge*) * orig->size);
    orig->edges[orig->size - 1] = e1;

    dest->size++;
    dest->edges = realloc(dest->edges, sizeof(Edge*) * dest->size);
    dest->edges[dest->size - 1] = e2;
}
