#include "world.h"

void init_world() {
    init_screen(-2, -2, 2, 2, 500, 500);
    num_objects = 2;
    objects = malloc(sizeof(object *) * num_objects);
    eye.x = 0;
    eye.y = 0;
    eye.z = -5;
    objects[0] = init_sphere(-1, 0, 0, .1, 0, 0, 0);
    objects[1] = malloc(sizeof(object));
    objects[1] = init_sphere(1, 0, 0, -.1, 0, 0, 1);

    objects[0]->color = blue;
    objects[1]->color = green;
}

void go() {
    display_objects();
    update_objects();
    SDL_Delay(500);
}

void display_objects() {
    clearScreen();
    int i = 0;
    while(i < num_objects) {
        double ts[3];
        ts[0] = objects[i]->x;
        ts[1] = objects[i]->y;
        ts[2] = objects[i]->z;
        matrix t = translation_matrix(ts);
        matrix to_render = multiply_matrix(t, *(objects[i]->mat));
        draw_to_screen(eye.x, eye.y, eye.z, &to_render, objects[i]->color);
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
                printf("COLLIDING!!!\n");
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

        }
        i++;
    }
}

/*
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
*/
