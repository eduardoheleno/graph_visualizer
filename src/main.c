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
        DrawText(TextFormat("%i", v->index), v->pos.x, v->pos.y, 20, WHITE);
    }
}

void render_shortest_path(unsigned int dest)
{
    Vert *dest_vert = vert_list->verts[dest];
    while (dest_vert->prev_vert != NULL) {
        Edge *to_render_edge = NULL;
        for (size_t i = 0; i < dest_vert->size; i++) {
            if (dest_vert->prev_vert->index == dest_vert->edges[i]->dest_vert->index) {
                to_render_edge = dest_vert->edges[i];
                break;
            }
        }
        DrawRectanglePro(to_render_edge->rec, (Vector2){0, 10}, to_render_edge->rot, DEFAULT_SHORTEST_EDGE_COLOR);

        dest_vert = dest_vert->prev_vert;
    }
}

int main(void)
{
    vert_list = malloc(sizeof(VertList));
    vert_list->size = 0;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window");
    SetTargetFPS(60);

    Rectangle rec = {0, 0, 0, 20};
    float rot = 0;

    bool test = false;
    bool test2 = false;

    while (!WindowShouldClose()) {
        watch_l_click(&rec, &rot);
        watch_r_click();

        if (IsKeyPressed(KEY_ENTER)) test = true;

        BeginDrawing();
            ClearBackground(RAYWHITE);
            graph_render();

            if (test) {
                find_shortest_path(vert_list, 0, 3);
                test = false;
                test2 = true;
            }

            if (test2) {
                render_shortest_path(3);
            }
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
