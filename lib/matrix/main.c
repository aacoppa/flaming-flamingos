#include <stdio.h>
#include "vector.h"
#include "../shapes/point.h"
#include "matrix.h"
int main() {
    /*
    struct point p1, p2, p3, eye;
    p1.x = 1;
    p1.y = 1;
    p1.z = 1;
    p2.x = 2;
    p2.y = 2;
    p2.z = 1;
    p3.x = 3;
    p3.y = 3;
    p3.z = 1;
    eye.x = 0;
    eye.y = 0;
    eye.z = 5;
    printf("directions %f, %f\n", get_direction(p1, p2, p3, eye), get_direction(p3, p2, p1, eye));
    vector v1 = init_vector( 0, 1, 1 );
    vector v2 = init_vector( 1, -1, 3);
    vector v3 = cross_product(v1, v2);
    print_vector(v3);
    */

    matrix a = init_identity(4);
    matrix b = init_matrix(4, 4);
    print_matrix(a);
    print_matrix(b);
    combine_matrices(&b, &a);
    print_matrix(b);
}
