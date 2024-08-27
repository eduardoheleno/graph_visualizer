#include "l_click.h"
#include "graph.h"
#include <raylib.h>

bool is_l_clicked = false;
bool is_orig_set = false;

Vert *orig_vert = NULL;
Vert *dest_vert = NULL;

extern VertList *vert_list;

void watch_l_click(Rectangle *rec, float *rot)
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (!is_l_clicked) {
            is_l_clicked = true;
            is_orig_set = false;

            orig_vert = get_clicked_vert();
        } else {
            is_l_clicked = false;
            dest_vert = get_clicked_vert();

            if (orig_vert != NULL && dest_vert != NULL) {
                set_edge(orig_vert, dest_vert, 10, rec, rot);
            }
        }
    }
    if (is_l_clicked && !is_orig_set) set_rec_origin(rec);
    if (is_l_clicked) set_rec_width(rec, rot);
}

void set_rec_origin(Rectangle *rec)
{
    Vector2 mouse_pos = GetMousePosition();
    rec->x = mouse_pos.x;
    rec->y = mouse_pos.y;

    is_orig_set = true;

    TraceLog(LOG_INFO, "Orig set");
}

void set_rec_width(Rectangle *rec, float *rot)
{
    Vector2 mouse_pos = GetMousePosition();
    float dx = mouse_pos.x - rec->x;
    float dy = mouse_pos.y - rec->y;

    if (dx < 0) dx *= -1;
    if (dy < 0) dy *= -1;

    float width = sqrtf((dx * dx) + (dy * dy));
    rec->width = width;
    *rot = (atan2f(mouse_pos.y - rec->y, mouse_pos.x - rec->x) * (180.0 / M_PI));
}

Vert *get_clicked_vert()
{
    for (size_t i = 0; i < vert_list->size; i++) {
        if (
            CheckCollisionPointCircle(
                GetMousePosition(),
                vert_list->verts[i]->pos,
                DEFAULT_VERT_RADIUS
            )
        ) {
            return vert_list->verts[i];
        }
    }

    return NULL;
}
