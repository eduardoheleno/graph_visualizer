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
            graph_render(vert_list);
            /* for (size_t i = 0; i < vert_list->size; i++) { */
            /*     Vert *v = vert_list->verts[i]; */
            /*     for (size_t j = 0; j < v->size; j++) { */
            /*         Edge *e = v->edges[j]; */
            /*         DrawRectanglePro(e->rec, (Vector2){0, 10}, e->rot, DEFAULT_EDGE_COLOR); */
            /*     } */

            /*     if (v->is_selected) { */
            /*         DrawCircleV(v->pos, DEFAULT_VERT_RADIUS, DEFAULT_SELECTED_VERT_COLOR); */
            /*     } else { */
            /*         DrawCircleV(v->pos, DEFAULT_VERT_RADIUS, DEFAULT_VERT_COLOR); */
            /*     } */
            /* } */
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
