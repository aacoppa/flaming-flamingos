#ifndef PHYSICS_BGT1E8WB

#define PHYSICS_BGT1E8WB
#include "world.h"
#include "interface.h"

void collide(object *, object *);
void sphere_to_sphere_collision(object *, object *);
void sphere_to_rect_collision(object *, object *);
void rect_to_rect_collision(object *, object *);

int colliding(object *, object *);
void collision(object *, object *);

void gravitate(object *);
#endif /* end of include guard: PHYSICS_BGT1E8WB */
