/* Rectangles
 */
#ifndef __CUBE_ACG
#define __CUBE_ACG 0
#define N_DIVISIONS 2 
#include "point.h" //For struct point
#include "../renderer.h" //For adding triangles to edge
#include "../matrix/matrix.h"
#include "../matrix/transformations.h"

struct face * get_box_faces(double, double, double,
                             double, double, double);
void draw_box(double, double, double,
               double, double, double, matrix *);
void draw_triangles_in_box(struct face *, matrix *);

struct face {
    struct point ** points;
};

void free_faces(struct face *);
#endif
