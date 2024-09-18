#include "r_click.h"

extern VertList *vert_list;

void watch_r_click(unsigned int *vert_index)
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        Vert *v = create_vert(GetMousePosition(), *vert_index);
        (*vert_index)++;

        vert_list->size++;
        vert_list->verts = realloc(vert_list->verts, sizeof(Vert*) * vert_list->size);
        vert_list->verts[vert_list->size - 1] = v;
    }
}
