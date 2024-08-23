#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

typedef struct RecList {
    Rectangle rec;
    float rot;
    struct RecList *next;
} RecList;

void set_rec_origin(Rectangle *rec, bool *is_orig_set)
{
    Vector2 mouse_pos = GetMousePosition();
    rec->x = mouse_pos.x;
    rec->y = mouse_pos.y;

    *is_orig_set = true;

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

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window");
    SetTargetFPS(60);

    RecList *rec_list = NULL;
    Rectangle rec = {0, 0, 0, 20};
    float rot = 0;
    Color c = RED;
    bool is_clicked = false;
    bool is_orig_set = false;

    while (!WindowShouldClose()) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (!is_clicked) {
                is_clicked = true;
                is_orig_set = false;
            } else {
                is_clicked = false;
                /* save_rec(&rec_list, rec, rot); */
            }
        }
        if (is_clicked && !is_orig_set) set_rec_origin(&rec, &is_orig_set);
        if (is_clicked) set_rec_width(&rec, &rot);

        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawRectanglePro(rec, (Vector2){0, 10}, rot, c);
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
