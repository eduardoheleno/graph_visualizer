#include "l_click.h"
#include <raylib.h>

bool is_l_clicked = false;
bool is_orig_set = false;

void watch_l_click(Rectangle *rec, float *rot)
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (!is_l_clicked) {
            is_l_clicked = true;
            is_orig_set = false;
        } else {
            is_l_clicked = false;
            /* save_rec(&rec_list, rec, rot); */
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
