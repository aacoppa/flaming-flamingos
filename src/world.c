#include "world.h"
void init_world() {

}

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
    int i = 0;
    while(i < num_objects) {
        update_velocities(objects[i]);
        i++;
    }
    i = 0;
    while(i < num_objects) {
        update_positions(objects[i]);
    }
}

void update_velocities(object * obj) {
    int i = 0;
    while(i < num_objects) {
        if(obj->object_number != objects[i]->object_number) {
            if(colliding(obj, objects[i])) {
                avoid_collision(obj, objects[i]);
            }
        } 
        i++;
    }
}

void update_positions() {
    int i = 0;
    while(i < num_objects) {
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
