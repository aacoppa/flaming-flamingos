#include "box.h"
#include "../matrix/vector.h"
#include "../matrix/matrix.h"
#include "fill.h"
#include "../screen.h"
#include "../renderer.h"
#include "sphere.h"

/*void print_point(struct point p) {
    printf("Point (%f, %f, %f)\n", p.x, p.y, p.z);
}
void test_vector(int, matrix *); */
int main(int argc, char ** argv) {
    /*
    matrix render = init_matrix(0, 4);
    draw_box(2, 2, 2, 0, 0, 0, &render);
    test_vector(32, &render);
    */
    //fill_test();
    struct point p1;
    p1.x = 0;
    p1.y = 0;
    p1.z = 0;

    struct point p2;
    p2.x = -.5;
    p2.y = -.5;
    p2.z = -1;

    struct point p3;
    p3.x = .5;
    p3.y = 0;
    p3.z = -1;

    SDL_Color s;
    s.r = 0;
    s.g = 0;
    s.b = 255;
    init_screen(-2, -2, 2, 2, 500, 500);
    matrix transformer = init_identity(4);

    matrix * m = malloc(sizeof(matrix));

    *m = init_matrix(4, 4);
    add_triangle_to_render(p1.x, p1.y, p1.z,
            p2.x, p2.y, p2.z,
            p3.x, p3.y, p3.z,
            m);
    int i = 0;
    while(i < 300) {
        printf("%d.1\n", i);
        matrix to_render = multiply_matrix(transformer, *m);
        print_matrix(to_render);
        printf("\n\n");
        printf("%d.2\n", i);
        draw_to_screen(0, 0, -5, &to_render, *(Uint32 *)&s);
        printf("%d.3\n", i);
        i++;
        SDL_Delay(20);
    }
    return 0;
}
/*
void test_vector(int startX, matrix * to_render) {
        struct point p1, p2, p3;
        p1.x = to_render->mat[startX-2][0];
        p1.y = to_render->mat[startX-2][1];
        p1.z = to_render->mat[startX-2][2];
        p2.x = to_render->mat[startX-1][0];
        p2.y = to_render->mat[startX-1][1];
        p2.z = to_render->mat[startX-1][2];
        p3.x = to_render->mat[startX][0];
        p3.y = to_render->mat[startX][1];
        p3.z = to_render->mat[startX][2];
        print_point(p1);
        print_point(p2);
        print_point(p3);
        vector v1 = get_vector(p2, p1);
        vector v2 = get_vector(p2, p3);
        print_vector(v1);
        print_vector(v2);
        printf("Cross\n");
        vector v3 = cross_product(v1, v2);
        print_vector(v3);
        struct point eye;
        eye.x = 0;
        eye.y = 0;
        eye.z = 5;
        vector v4 = get_vector(p2, eye);
        printf("Eye\n");
        print_vector(v4);
        double dot = dot_product(v3, v4);
        printf("Dot: %f\n", dot);
}
void add_triangle_to_render( double x1, double y1, double z1,
                           double x2, double y2, double z2,
                           double x3, double y3, double z3, matrix * to_render) {
        //Order points in a counter clockwise order

    (*to_render) = add_columns((*to_render), 3);
    to_render->mat[to_render->width - 3][0] = x1;
    to_render->mat[to_render->width - 3][1] = y1;
    to_render->mat[to_render->width - 3][2] = z1;
    to_render->mat[to_render->width - 3][3] = 1;
    to_render->mat[to_render->width - 2][0] = x2;
    to_render->mat[to_render->width - 2][1] = y2;
    to_render->mat[to_render->width - 2][2] = z2;
    to_render->mat[to_render->width - 2][3] = 1;
    to_render->mat[to_render->width - 1][0] = x3;
    to_render->mat[to_render->width - 1][1] = y3;
    to_render->mat[to_render->width - 1][2] = z3;
    to_render->mat[to_render->width - 1][3] = 1;
}
*/
