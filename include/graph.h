#ifndef GRAPH_H_
#define GRAPH_H_

#include <raylib.h>
#include <stdlib.h>

#define DEFAULT_VERT_RADIUS 20

#define DEFAULT_EDGE_COLOR RED
#define DEFAULT_SHORTEST_EDGE_COLOR GREEN

#define DEFAULT_VERT_COLOR BLACK
#define DEFAULT_SELECTED_VERT_COLOR GREEN

typedef struct Vert {
    Vector2 pos;
    size_t size;
    bool is_selected;
    unsigned int index;
    int shortest_path_value;
    bool is_explored;

    struct Vert *prev_vert;
    struct Edge **edges;
} Vert;

typedef struct Edge {
    size_t weight;
    Rectangle rec;
    float rot;

    Vert *dest_vert;
} Edge;

typedef struct VertList {
    size_t size;
    Vert **verts;
} VertList;

Vert *create_vert(Vector2 pos, unsigned int index);
Edge *create_edge(Vert *dest, size_t weight, Rectangle rec, float rot);
void set_edge(Vert *orig, Vert *dest, size_t weight,
    Rectangle *rec, float *rot);
void reset_vert_list(VertList *vert_list);
bool find_shortest_path(VertList *vert_list, unsigned int orig, unsigned int dest);

#endif // GRAPH_H_
