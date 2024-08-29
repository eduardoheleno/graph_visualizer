#include "l_click.h"
#include "graph.h"
#include <raylib.h>

Vert *orig_vert = NULL;
Vert *dest_vert = NULL;

extern VertList *vert_list;

void graph_render()
{
    if (vert_list == NULL || vert_list->size == 0) return;

    for (size_t i = 0; i < vert_list->size; i++) {
        Vert *v = vert_list->verts[i];
        for (size_t j = 0; j < v->size; j++) {
            Edge *e = v->edges[j];
            if (e->dest_vert->index < v->index) continue;

            DrawRectanglePro(e->rec, (Vector2){0, 10}, e->rot, DEFAULT_EDGE_COLOR);
        }

        if (v->is_selected) {
            DrawCircleV(v->pos, DEFAULT_VERT_RADIUS, DEFAULT_SELECTED_VERT_COLOR);
        } else {
            DrawCircleV(v->pos, DEFAULT_VERT_RADIUS, DEFAULT_VERT_COLOR);
        }
    }
}

void watch_l_click(Rectangle *rec, float *rot)
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (orig_vert == NULL) {
            orig_vert = get_clicked_vert();
            if (orig_vert != NULL) {
                orig_vert->is_selected = true;
            }

            return;
        }
        if (dest_vert == NULL) {
            dest_vert = get_clicked_vert();
            if (dest_vert == NULL) {
                return;
            }
        }

        set_rec_origin(rec);
        set_rec_width(rec, rot);
        set_edge(orig_vert, dest_vert, 10, rec, rot);

        orig_vert->is_selected = false;

        orig_vert = NULL;
        dest_vert = NULL;
    }
}

void set_rec_origin(Rectangle *rec)
{
    rec->x = orig_vert->pos.x;
    rec->y = orig_vert->pos.y;
}

void set_rec_width(Rectangle *rec, float *rot)
{
    float dx = dest_vert->pos.x - rec->x;
    float dy = dest_vert->pos.y - rec->y;

    if (dx < 0) dx *= -1;
    if (dy < 0) dy *= -1;

    float width = sqrtf((dx * dx) + (dy * dy));
    rec->width = width;
    *rot = (atan2f(dest_vert->pos.y - rec->y, dest_vert->pos.x - rec->x) * (180.0 / M_PI));
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
