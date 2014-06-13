#include "matrix/matrix.h"
#include "matrix/transformations.h"
#include "shapes/sphere.h"
#include "world.h"
#include <stdlib.h>

void init_world() {
    num_objects = 0;
    objects = malloc(sizeof(object));
    eye.x = 0;
    eye.y = 5;
    eye.z = 10;
}

void go() {
    display_objects();
    update_objects();
}

void display_objects() {
    matrix * to_render = malloc(sizeof(matrix));
    *to_render = init_identity(4);
    int i = 0;
    printf("num_objects: %d\n", num_objects);
    while(i < num_objects) {
        printf("i: %d\n", i);
        printf("width: %d, height: %d\n", objects[i]->mat->width, objects[i]->mat->height);
        combine_matrices(to_render, objects[i]->mat);
        i++;
    }

    SDL_Color s;
    s.r = 0;
    s.g = 0;
    s.b = 255;
    draw_to_screen(eye.x, eye.y, eye.z, to_render, *(Uint32 *)&s);
}

void update_objects() {
    update_velocities();
    update_positions();
}

void update_velocities() {
    int i, j;
    for(i = 0; i < num_objects; i++) {
        object *obj = objects[i];
        for(j = i + 1; j < num_objects; j++) {
            if(colliding(obj, objects[j])) {
                collision(obj, objects[j]);
            }
        }
    }
}

void update_positions() {
    int i = 0;
    while(i < num_objects) {
        if(objects[i]->movable) {
            objects[i]->x = objects[i]->x + objects[i]->vx;
            objects[i]->y = objects[i]->y + objects[i]->vy;
            objects[i]->z = objects[i]->z + objects[i]->vz;

            /* Transform the point matrix now
            *
            */
            double ts[3];
            ts[0] = objects[i]->x;
            ts[1] = objects[i]->y;
            ts[2] = objects[i]->z;
            matrix t = translation_matrix(ts);
            multiply_matrix_onto_self(t, objects[i]->mat);
        }
    }
}

void add_object() {
    num_objects += 1;
    int index = num_objects - 1;

    objects = realloc(objects, (num_objects + 1) * sizeof(object));
    objects[index] = malloc(sizeof(object));

    double x = ( (double)rand() / (double)RAND_MAX ) * 2.0,
        y = ( (double)rand() / (double)RAND_MAX ) * 2.0,
        z = ( (double)rand() / (double)RAND_MAX ) * 2.0,
        r = 0.4;
    double vx = ( (double)rand() / (double)RAND_MAX ) * 0.1,
        vy = ( (double)rand() / (double)RAND_MAX ) * 0.1,
        vz = ( (double)rand() / (double)RAND_MAX ) * 0.1;

    matrix mat = init_identity(4);
    draw_sphere(x, y, z, r, &mat);

    objects[index]->id = SPHERE_ID;
    objects[index]->object_number = index;
    objects[index]->movable = 1;
    objects[index]->r = 0.4;
    objects[index]->x = x;
    objects[index]->y = y;
    objects[index]->z = z;
    objects[index]->vx = vx;
    objects[index]->vy = vy;
    objects[index]->vz = vz;
    objects[index]->mat = malloc(sizeof(matrix));
    *(objects[index]->mat) = mat;
}
