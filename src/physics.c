#ifndef PHYSICS_4AJ7MSKO

#define PHYSICS_4AJ7MSKO


#include "screen.h"
#include "matrix/vector.h"
#include "world.h"
#include "interface.h"
#include "physics.h"
#include <stdio.h>


void collide(object *obj0, object *obj1) {
    if (obj0->id != SPHERE_ID && obj1->id == SPHERE_ID) {
        object temp = *obj0;
        *obj0 = *obj1;
        *obj1 = temp;
    }

    if(obj0->id == SPHERE_ID && obj1->id == SPHERE_ID)
        sphere_to_sphere_collision(obj0, obj1);
    else if(obj0->id == SPHERE_ID && obj1->id == RECT_ID)
        sphere_to_rect_collision(obj0, obj1);
    else
        rect_to_rect_collision(obj0, obj1);
}

void sphere_to_sphere_collision(object *ball0, object *ball1) {
    vector diff;
    diff.x = ball0->x - ball1->x;
    diff.y = ball0->y - ball1->y;
    diff.z = ball0->z - ball1->z;

    //Return if not colliding
    if (magnitude(diff) > ball0->r + ball1->r)
        return;

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

void sphere_to_rect_collision(object * ball, object * box) {

    matrix faces = *(box->mat);
    struct point p1, p2, p3, int_pt;
    vector nml, ray_dir, plane_pt, ray_pt, int_vec, v1, v2;
    int i;
    double t;

    /*
     * Calculate time at which ray from radius of circle intersects
     * with triangle face.  Make sure that time is within correct range.
     */
    for (i = 6; i < faces.width; i += 3) {
        p1.x = faces.mat[i - 2][0];
        p1.y = faces.mat[i - 2][1];
        p1.z = faces.mat[i - 2][2];
        p2.x = faces.mat[i - 1][0];
        p2.y = faces.mat[i - 1][1];
        p2.z = faces.mat[i - 1][2];
        p3.x = faces.mat[i][0];
        p3.y = faces.mat[i][1];
        p3.z = faces.mat[i][2];

        v1 = get_vector(p1, p2);
        v2 = get_vector(p3, p2);

        nml = cross_product(v1, v2);
        normalize(&nml);

        ray_dir = nml;
        ray_dir.x *= -1;
        ray_dir.y *= -1;
        ray_dir.z *= -1;

        plane_pt.x = p1.x;
        plane_pt.y = p1.y;
        plane_pt.z = p1.z;

        ray_pt.x = ball->x;
        ray_pt.y = ball->y;
        ray_pt.z = ball->z;

        t = (dot_product(nml, plane_pt) - dot_product(nml, ray_pt)) / (dot_product(nml, ray_dir));

        int_vec.x = t * ray_dir.x;
        int_vec.y = t * ray_dir.y;
        int_vec.z = t * ray_dir.z;

        if(t < 0 || magnitude(int_vec) > ball->r)
            continue;

        ball->vx *= -1;
        ball->vy *= -1;
        ball->vz *= -1;
        break;
    }
    return;
}

void rect_to_rect_collision(object * box0, object * box1) {
    return;
}

void gravitate(object *obj) {
}
#endif /* end of include guard: PHYSICS_4AJ7MSKO */
