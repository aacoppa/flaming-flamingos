#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "renderer.h"
#include "shapes/box.h"
#include "shapes/sphere.h"
#include "world.h"

int main(int argc, char ** argv) {
    /*
    init_world();
    while(1) { 
        go();
    }
    return 0;
    */

    struct point p1;
    p1.x = 1;
    p1.y = 1;
    p1.z = 0;

    struct point p2;
    p2.x = -1;
    p2.y = -1;
    p2.z = 0;

    struct point p3;
    p3.x = 1;
    p3.y = -1;
    p3.z = 0;

    init_screen(-2, -2, 2, 2, 500, 500);
    matrix transformer = init_identity(4);

    matrix * m = malloc(sizeof(matrix));

    *m = init_matrix(4, 4);
//    add_triangle_to_render(p1.x, p1.y, p1.z,
//            p2.x, p2.y, p2.z,
//            p3.x, p3.y, p3.z,
//            m);
    
    draw_sphere(-1, 0, 0, 1, m);

    while(1) {
        clearScreen();
        matrix transformer = init_identity(4);
        matrix rend = multiply_matrix(transformer, *m);
        draw_to_screen(0, 0, -5, &rend, blue);
        renderScreen();
    }
}
