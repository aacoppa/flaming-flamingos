#include "world.h"

void go() {
    update_objects();
    display_objects();
}

void display_objects() {
    matrix * to_render = malloc(sizeof(matrix));
    *to_render = init_identity(4);
    int i = 0;
    while(i < num_objects) {
        combine_matrices(to_render, objects[i]->mat);
        i++;
    }
    draw_to_screen(eye.x, eye.y, eye.z, to_render);
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
        if(objects[i].movable) {
        objects[i].x = objects[i].x + objects[i].vx;
        objects[i].y = objects[i].y + objects[i].vy;
        objects[i].z = objects[i].z + objects[i].vz;

        /* Transform the point matrix now
         *
         */
        double ts[3];
        ts[0] = objects[i].x;
        ts[1] = objects[i].y;
        ts[2] = objects[i].z;
        matrix t = translation_matrix(ts);
        multiply_matrix_onto_self(t, objects[i]->mat);
        }
    }
}
