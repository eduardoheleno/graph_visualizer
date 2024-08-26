#include "r_click.h"
#include "graph.h"
#include <raylib.h>

extern VertList *vert_list;

void watch_r_click()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        Vert *v = create_vert(GetMousePosition());

        vert_list->size++;
        vert_list->head = realloc(vert_list->head, sizeof(Vert*) * vert_list->size);
        vert_list->head[vert_list->size - 1] = v;
    }
}
