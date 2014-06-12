/* 
 * Sphere-drawing algortthim
 * returns array of points that then need
 * to be connected, as seen in
 * interpret.c 
 *  case SPHERE:
 */
#ifndef __TRANS_SPH_AJS
#define __TRANS_SPH_AJS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "line.h"
#include "point.h"
#include "../renderer.h"
#define N_POINTS 18

//void add_line_to_edge( double, double, double, double, double, double );
void draw_sphere(double, double, double, double, matrix *);
struct point ** get_sphere_points( double, double, double, double );
void draw_triangles_in_sphere(struct point **, matrix *);
void free_points(struct point **);
void print_point( struct point );
#endif
