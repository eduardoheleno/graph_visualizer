#include "reset.h"

void reset_vert_list(VertList *vert_list)
{
    for (size_t i = 0; i < vert_list->size; i++) {
        Vert *v = vert_list->verts[i];
        for (size_t j = 0; j < v->size; j++) {
            free(v->edges[j]);
        }

        free(v->edges);
        free(v);
    }

    free(vert_list->verts);
    vert_list->verts = NULL;
    vert_list->size = 0;
}
