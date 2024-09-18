#include "graph.h"
#include <raylib.h>

Vert *create_vert(Vector2 pos, unsigned int index)
{
    Vert *v = malloc(sizeof(Vert));
    v->pos = pos;
    v->is_selected = false;
    v->is_explored = false;
    v->edges = NULL;
    v->prev_vert = NULL;
    v->index = index;
    v->shortest_path_value = -1;
    v->size = 0;

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

Vert *get_smallest_not_explored_vert(VertList *vert_list)
{
    Vert *v = NULL;
    for (size_t i = 0; i < vert_list->size; i++) {
        if (
            (
                v == NULL &&
                !vert_list->verts[i]->is_explored &&
                vert_list->verts[i]->shortest_path_value > 0
            ) ||
            (
                !vert_list->verts[i]->is_explored &&
                vert_list->verts[i]->shortest_path_value > 0 &&
                v->shortest_path_value > vert_list->verts[i]->shortest_path_value
            )
        ) {
            v = vert_list->verts[i];
        }
    }

    return v;
}

void reset_shortest_path(VertList *vert_list)
{
    for (size_t i = 0; i < vert_list->size; i++) {
        Vert *v = vert_list->verts[i];
        v->shortest_path_value = -1;
        v->is_explored = false;
        v->prev_vert = NULL;
    }
}

// Dijkstra's algorithm
bool find_shortest_path(VertList *vert_list, unsigned int orig, unsigned int dest)
{
    if (vert_list == NULL || vert_list->size == 0) return false;
    if (vert_list->size - 1 < orig) return false;

    unsigned int cur_orig_index = orig;

    Vert *cur_v = vert_list->verts[cur_orig_index];
    cur_v->shortest_path_value = 0;
    cur_v->is_explored = true;

    while (!vert_list->verts[dest]->is_explored) {
        for (size_t i = 0; i < cur_v->size; i++) {
            Edge *e = cur_v->edges[i];
            if (
                !e->dest_vert->is_explored &&
                (
                    e->dest_vert->shortest_path_value < 0 ||
                    e->dest_vert->shortest_path_value > cur_v->shortest_path_value + (int)e->weight
                )
            ) {
                e->dest_vert->shortest_path_value = cur_v->shortest_path_value + e->weight;
                e->dest_vert->prev_vert = cur_v;
            }
        }

        cur_v = get_smallest_not_explored_vert(vert_list);
        if (cur_v == NULL) {
            return false;
        }

        cur_v->is_explored = true;
    }

    return true;
}
