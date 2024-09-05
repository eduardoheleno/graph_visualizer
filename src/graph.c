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

// Dijkstra's algorithm
void find_shortest_path(VertList *vert_list, unsigned int orig, unsigned int dest)
{
    if (vert_list == NULL || vert_list->size == 0) return;

    unsigned int cur_orig_index = orig;
    Vert *v_buffer = NULL;
    Vert *cur_v = vert_list->verts[cur_orig_index];
    cur_v->shortest_path_value = 0;

    while (cur_orig_index != dest) {
        for (size_t i = 0; i < cur_v->size; i++) {
            Edge *e = cur_v->edges[i];
            if (
                !e->dest_vert->is_explored &&
                (e->dest_vert->shortest_path_value == -1 || e->dest_vert->shortest_path_value > cur_v->shortest_path_value + (int)e->weight)
            ) {
                e->dest_vert->shortest_path_value = cur_v->shortest_path_value + (int)e->weight;

                if (v_buffer == NULL) {
                    v_buffer = e->dest_vert;
                } else {
                    if (e->dest_vert->shortest_path_value < v_buffer->shortest_path_value) {
                        v_buffer = e->dest_vert;
                    }
                }
            } else if (!e->dest_vert->is_explored) {
                if (v_buffer == NULL) {
                    v_buffer = e->dest_vert;
                } else {
                    if (e->dest_vert->shortest_path_value < v_buffer->shortest_path_value) {
                        v_buffer = e->dest_vert;
                    }
                }
            }
        }

        cur_v->is_explored = true;
        v_buffer->prev_vert = cur_v;
        cur_v = v_buffer;
        cur_orig_index = cur_v->index;

        v_buffer = NULL;
    }
}
