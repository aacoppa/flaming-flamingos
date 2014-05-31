#ifndef __RENDERER_ACG
#define __RENDERER_ACG 1
#include <stdio.h>
#include "matrix/matrix.h"
#include "matrix/vector.h"
#include "screen.h"
#include "shapes/point.h"
#include "shapes/line.h"
#include "shapes/fill.h"


int width, height; 

void draw_to_screen(double, double, double, matrix * to_render, Uint32);
void init_screen(double, double, double, double,
                 int, int);
void convert_from_screen();
void convert_to_eye_coordinates(double, double, double, matrix *);
void add_triangle_to_render(double, double, double,
                          double, double, double,
                          double, double, double, matrix *);
void draw_triangles(matrix *, struct point, Uint32);

double sxl, syl, sxr, syr; //Bottom left, top rigt
struct point eye;
#endif
