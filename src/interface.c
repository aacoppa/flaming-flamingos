#include "interface.h"

object * init_sphere(double x, double y, double z, double vx, double vy, double vz) {
    object * obj = malloc(sizeof(object));
    obj->id = SPHERE_ID;
    obj->x = x;
    obj->y = y;
    obj->z = z;
    obj->vx = vx;
    obj->vy = vy;
    obj->vz = vz;
    obj->r = .5;
    obj->movable = 1;
    draw_sphere(x, y, z, .5, obj->mat);
    return obj;
}
