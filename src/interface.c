#include "interface.h"

object * init_sphere(double x, double y, double z, double vx, double vy, double vz, int on) {
    object * obj = malloc(sizeof(object));
    obj->object_number = on;
    obj->id = SPHERE_ID;
    obj->x = x;
    obj->y = y;
    obj->z = z;
    obj->vx = vx;
    obj->vy = vy;
    obj->vz = vz;
    obj->r = .5;
    obj->movable = 1;
    obj->mat = malloc(sizeof(matrix));
    *(obj->mat) = init_identity(4);
    draw_sphere(x, y, z, .5, obj->mat);
    return obj;
}
