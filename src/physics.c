#ifndef PHYSICS_4AJ7MSKO

#define PHYSICS_4AJ7MSKO


#include "screen.h"
#include "matrix/vector.h"
#include "world.h"
#include "interface.h"
#include "physics.h"
#include <stdio.h>

/**
 * Spherical collision function that bases collision on the radius of two
 * objects and the distance between their centers.
 **/
int colliding(object *ball0, object *ball1) {
    vector diff;
    diff.x = ball0->x - ball1->x;
    diff.y = ball0->y - ball1->y;
    diff.z = ball0->z - ball1->z;

    print_vector(diff); 
    printf("%f\n", magnitude(diff));
    if (magnitude(diff) > ball0->r + ball1->r)
        return 0;
    else
        return 1;
}

/**
 * Update the velocity vectors of the objects based on how they collide.
 **/
void collision(object *ball0, object *ball1) {
    //Calculate vector of object center line
    vector cline0, cline1, vel0, vel1;
    cline0.x = ball0->x - ball1->x;
    cline0.y = ball0->y - ball1->y;
    cline0.z = ball0->z - ball1->z;

    cline1.x = ball1->x - ball0->x;
    cline1.y = ball1->y - ball0->y;
    cline1.z = ball1->z - ball0->z;

    vel0.x = ball0->vx;
    vel0.y = ball0->vy;
    vel0.z = ball0->vz;

    vel1.x = ball1->vx;
    vel1.y = ball1->vy;
    vel1.z = ball1->vz;

    //Calculate cosine of angle between vectors using LOC / dot product
    double m0 = dot_product(cline0, vel1) / magnitude(cline0),
        m1 = dot_product(cline1, vel0) / magnitude(cline1);


    //Use the cosine to calculate the magnitude of collision vector
    double cmag0 = magnitude(cline0),
        cmag1 = magnitude(cline1);
    vector c0, c1;

    c0.x = ( cline0.x / cmag0 ) * m0;
    c0.y = ( cline0.y / cmag0 ) * m0;
    c0.z = ( cline0.z / cmag0 ) * m0;

    c1.x = ( cline1.x / cmag1 ) * m1;
    c1.y = ( cline1.y / cmag1 ) * m1;
    c1.z = ( cline1.z / cmag1 ) * m1;

    //Add collision vector to movement vector to get new vector
    ball0->vx += -c1.x + c0.x;
    ball0->vy += -c1.y + c0.y;
    ball0->vz += -c1.z + c0.z;

    ball1->vx += -c0.x + c1.x;
    ball1->vy += -c0.y + c1.y;
    ball1->vz += -c0.z + c1.z;
}

/**
 * Apply gravitational force to objects.
 **/
void gravitate(object *obj) {
}
#endif /* end of include guard: PHYSICS_4AJ7MSKO */
