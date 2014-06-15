#include "world.h"

void init_world() {
    init_screen(-2, -2, 2, 2, 500, 500);
    init_boundaries();

    num_objects += 2;
    objects = realloc(objects, sizeof(object *) * num_objects);
    objects[num_objects - 2] = init_sphere(-1, 0.3, 0, .02, -0.01, 0, num_objects - 2);
    objects[num_objects - 1] = malloc(sizeof(object));
    objects[num_objects - 1] = init_sphere(1, -0.5, 0, -.02, .02, 0, num_objects - 1);

    objects[num_objects - 1]->should_fill = 0;
    objects[num_objects - 1]->r = 0.2;
    objects[num_objects - 2]->r = 0.5;
    objects[num_objects - 2]->color = blue;
    objects[num_objects - 1]->color = green;

    eye.x = 0;
    eye.y = 0;
    eye.z = -5;
}

void init_boundaries() {
    num_objects = 1;
    objects = malloc(sizeof(object *) * num_objects);

    objects[0] = init_box(0, 4, 4, -2, 0, 2, 0);
    objects[0]->color = white;

    /*
    objects[1] = init_box(0, 4, 10, 2, 0, 5, 0);
    objects[1]->color = white;

    objects[2] = init_box(8, 8, 0, 0, 0, 7.5, 0);
    objects[2]->color = white;

    objects[3] = init_box(8, 0, 10, 0, 2, 10, 0);
    objects[3]->color = white;

    objects[4] = init_box(8, 8, 0, 0, 0, 2.5, 0);
    objects[4]->color = white;

    objects[3] = init_box(8, 0, 10, 0, -2, 5, 0);
    objects[3]->color = white;
    */
}

void go() {
    display_objects();
    update_objects();
}

void display_objects() {
    clearScreen();
    int i = 0;
    while(i < num_objects) {
        double ts[3];
        ts[0] = objects[i]->x;
        ts[1] = objects[i]->y;
        ts[2] = objects[i]->z;

        matrix transformer = rotation_matrix_x(objects[i]->theta_x);
        multiply_matrix_onto_self(rotation_matrix_y(objects[i]->theta_y),
                                 &transformer);
        multiply_matrix_onto_self(rotation_matrix_z(objects[i]->theta_z),
                                 &transformer);
        multiply_matrix_onto_self(translation_matrix(ts),
                                 &transformer);

        //Make sure to translate to the origin before scaling
        if (objects[i]->id == SPHERE_ID) {
            double rs[3];
            rs[0] = objects[i]->r;
            rs[1] = rs[0];
            rs[2] = rs[0];
            multiply_matrix_onto_self(scale_matrix(rs), &transformer);
        }
        matrix to_render = multiply_matrix(transformer, *(objects[i]->mat));


        draw_to_screen(eye.x, eye.y, eye.z, &to_render,
                objects[i]->color, objects[i]->should_fill);
        i++;
    }

    renderScreen();
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

            objects[i]->theta_x += objects[i]->rx;
            objects[i]->theta_y += objects[i]->ry;
            objects[i]->theta_z += objects[i]->rz;

            /* Transform the point matrix now
            *
            */

        }
        i++;
    }
}
