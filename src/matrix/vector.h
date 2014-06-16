#ifndef __VECTOR_ACG
#define __VECTOR_ACG 1

#include "../shapes/point.h"
#include <stdio.h>
typedef struct {
    double x;
    double y;
    double z;
} vector;

vector init_vector(double, double, double);
vector get_vector(struct point, struct point);
double dot_product(vector, vector);
vector cross_product(vector, vector);
double get_direction(struct point, struct point, struct point, struct point);
double magnitude(vector);
void normalize(vector *);
void print_vector(vector);
#endif
