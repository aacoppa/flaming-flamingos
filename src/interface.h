/* Hide all of implementation details through here
 * -Hopefully all matrix work can be on this side of the
 *  interface
 *
 *  SORT OF OBJECT ORIENTED APPROACH HONESTLY...
 *
 *  WORLD SIDE
 *  ==========
 *  Create objects with properties and functions but can't actually
 *  see how they are displayed, etc...
 *  Instead the other side fills function pointers for collision testing
 *  and stuff
 *
 *  THIS SIDE
 *  =========
 *  Implements the missing functions
 */
#ifndef INTERFACE_HQ0DKX03

#define INTERFACE_HQ0DKX03
#include "matrix/matrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "renderer.h"
#include "matrix/matrix.h"
#include "shapes/sphere.h"

#define SPHERE_ID   1
#define RECT_ID     2

/* Use an object struct to represent
 * the different things that will be
 * bouncing around
 */

typedef struct {
    int id;
    //int object_number;
    int movable;
    double r;
    double x, y, z; //current x, y, z
    matrix * mat; //current position matrix
    double vx, vy, vz, rx, ry, rz; //angular and regular velocitys
} object;

object * init_sphere(double, double, double,
                     double, double, double);


#endif /* end of include guard: INTERFACE_HQ0DKX03 */
