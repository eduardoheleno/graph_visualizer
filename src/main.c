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

void vert_render()
{
    if (vert_list == NULL || vert_list->size == 0) return;

    for (size_t i = 0; i < vert_list->size; i++) {
        Vert *v = vert_list->verts[i];
        if (v->is_selected) {
            DrawCircleV(v->pos, DEFAULT_VERT_RADIUS, DEFAULT_SELECTED_VERT_COLOR);
        } else {
            DrawCircleV(v->pos, DEFAULT_VERT_RADIUS, DEFAULT_VERT_COLOR);
        }
        DrawText(TextFormat("%i", v->index), v->pos.x, v->pos.y, 20, WHITE);
    }
}

void edge_render()
{
    if (vert_list == NULL || vert_list->size == 0) return;

    for (size_t i = 0; i < vert_list->size; i++) {
        Vert *v = vert_list->verts[i];
        for (size_t j = 0; j < v->size; j++) {
            Edge *e = v->edges[j];
            if (e->dest_vert->index < v->index) continue;

            DrawRectanglePro(e->rec, (Vector2){0, 10}, e->rot, DEFAULT_EDGE_COLOR);
        }
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

int main(int argc, char **argv)
{
    if (argc < 3) {
        printf("./spv [ORIG] [DEST]\n");
        return 1;
    }

    int orig_vert = atoi(argv[1]);
    int dest_vert = atoi(argv[2]);

    vert_list = malloc(sizeof(VertList));
    vert_list->size = 0;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Shortest path");
    SetTargetFPS(60);

    Rectangle rec = {0, 0, 0, 20};
    float rot = 0;

    bool should_find_shortest_path = false;
    bool should_render_shortest_path = false;

    while (!WindowShouldClose()) {
        watch_l_click(&rec, &rot);
        watch_r_click();

        if (IsKeyPressed(KEY_ENTER)) should_find_shortest_path = true;

        BeginDrawing();
            ClearBackground(RAYWHITE);

            edge_render();
            if (should_find_shortest_path) {
                reset_vert_list(vert_list);
                if (!find_shortest_path(vert_list, orig_vert, dest_vert)) {
                    printf("Target destination doesn't exists inside graph\n");
                    return 1;
                }
                should_find_shortest_path = false;
                should_render_shortest_path = true;
            }

            if (should_render_shortest_path) {
                render_shortest_path(dest_vert);
            }
            vert_render();

        EndDrawing();
    }
    CloseWindow();

    return 0;
}
