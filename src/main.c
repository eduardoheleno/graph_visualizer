#include <raylib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "graph.h"
#include "l_click.h"
#include "r_click.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define DEFAULT_EDGE_COLOR RED
#define DEFAULT_VERT_COLOR BLACK

VertList *vert_list = NULL;

int main(void)
{
    vert_list = malloc(sizeof(VertList));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window");
    SetTargetFPS(60);

    Rectangle rec = {0, 0, 0, 20};
    float rot = 0;

    while (!WindowShouldClose()) {
        watch_l_click(&rec, &rot);
        watch_r_click();

        BeginDrawing();
            ClearBackground(RAYWHITE);

            for (size_t i = 0; i < vert_list->size; i++) {
                Vert *v = vert_list->verts[i];
                for (size_t j = 0; j < v->size; j++) {
                    Edge *e = v->edges[j];
                    DrawRectanglePro(e->rec, (Vector2){0, 10}, e->rot, DEFAULT_EDGE_COLOR);
                }
                DrawCircleV(vert_list->verts[i]->pos, DEFAULT_VERT_RADIUS, DEFAULT_VERT_COLOR);
            }
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
