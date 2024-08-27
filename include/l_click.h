#ifndef L_CLICK_H_
#define L_CLICK_H_

#include "graph.h"

#include <stdbool.h>
#include <raylib.h>
#include <math.h>

void watch_l_click(Rectangle *rec, float *rot);
void set_rec_origin(Rectangle *rec);
void set_rec_width(Rectangle *rec, float *rot);
Vert *get_clicked_vert();

#endif // L_CLICK_H_
