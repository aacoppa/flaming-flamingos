#ifndef FILL_CE86T52I
#define FILL_CE86T52I

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "point.h"
#include "../matrix/matrix.h"

#define TOP_TRIANGLE 2
#define BOTTOM_TRIANGLE 3
#define BOTH 4


int fill_test();
void draw_top(struct point, struct point, struct point, matrix *);
void draw_bottom(struct point, struct point, struct point, matrix *);
matrix * fill_triangle(struct point pa, struct point pb, struct point pc);

//PRIVATE
int special_case(struct point p1, struct point p2, 
                 struct point p3, matrix * lines);
#endif /* end of include guard: FILL_CE86T52I */
