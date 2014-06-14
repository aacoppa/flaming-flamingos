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

    obj->rx = .01;
    obj->ry = .01;
    obj->rz = 0;

    obj->theta_x = 0;
    obj->theta_y = 0;
    obj->theta_z = 0;

    obj->r = .5;
    obj->movable = 1;
    obj->should_fill = 0;
    obj->mat = malloc(sizeof(matrix));
    *(obj->mat) = init_identity(4);
    draw_sphere(0, 0, 0, 1, obj->mat);
    return obj;
}
