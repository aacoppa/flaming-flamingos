#include "world.h"

void init_world() {
    init_screen(-2, -2, 2, 2, 500, 500);
    init_boundaries();

    num_objects += 2;
    objects = realloc(objects, sizeof(object *) * num_objects);
    objects[num_objects - 2] = init_sphere(-1, 0.3, 2, .02, -0.01, 0, num_objects - 2);
    objects[num_objects - 1] = malloc(sizeof(object));
    objects[num_objects - 1] = init_sphere(1, -0.5, 2, -.02, .02, 0, num_objects - 1);

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
    num_objects = 6;
    objects = malloc(sizeof(object *) * num_objects);

    objects[0] = init_box(4, 4, 4, -4, 0, 2, 0);
    objects[0]->color = white;

    objects[1] = init_box(4, 4, 4, 4, 0, 2, 1);
    objects[1]->color = white;

    objects[2] = init_box(4, 4, 4, 0, 0, 6, 0);
    objects[2]->color = white;

    objects[3] = init_box(4, 4, 4, 0, -4, 2, 0);
    objects[3]->color = white;

    objects[4] = init_box(4, 4, 4, 0, 4, 2, 0);
    objects[4]->color = white;

    objects[5] = init_box(4, 4, 4, 0, 0, -2, 0);
    objects[5]->visible = 0;
}

void go() {
    display_objects();
    update_objects();
}

void display_objects() {
    clearScreen();
    int i = 0;
    while(i < num_objects) {
        matrix transformer = init_identity(4);

        if(objects[i]->movable) {
            double ts[3], rs[3];
            ts[0] = objects[i]->x;
            ts[1] = objects[i]->y;
            ts[2] = objects[i]->z;

            rs[0] = objects[i]->r;
            rs[1] = rs[0];
            rs[2] = rs[0];

            transformer = rotation_matrix_x(objects[i]->theta_x);
            multiply_matrix_onto_self(rotation_matrix_y(objects[i]->theta_y),
                                    &transformer);
            multiply_matrix_onto_self(rotation_matrix_z(objects[i]->theta_z),
                                    &transformer);

            multiply_matrix_onto_self(scale_matrix(rs), &transformer);

            multiply_matrix_onto_self(translation_matrix(ts),
                                    &transformer);

        }
        matrix to_render = multiply_matrix(transformer, *(objects[i]->mat));

        if(objects[i]->visible) {
            draw_to_screen(eye.x, eye.y, eye.z, &to_render,
                    objects[i]->color, objects[i]->should_fill);
        }

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
            collide(obj, objects[j]);
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
