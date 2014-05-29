#include "vector.h"
vector init_vector(double x, double y, double z) {
    vector v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}
vector get_vector(struct point p1, struct point p2) {
    vector v;
    v.x = p1.x - p2.x;
    v.y = p1.y - p2.y;
    v.z = p1.z - p2.z;
    return v;
}

double dot_product(vector v1, vector v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
vector cross_product(vector v1, vector v2) {
    vector ret;
    ret.x = v1.y * v2.z - v1.z * v2.y;
    ret.y = v1.z * v2.x - v1.x * v2.z;
    ret.z = v1.x * v2.y - v1.y * v2.x;
    return ret;
}

double get_direction(struct point p1, struct point p2, struct point p3, struct point eye) {
    vector v1 = get_vector(p1, p2);
    vector v2 = get_vector(p3, p2);
    vector normal = cross_product( v1, v2 );
    vector to_eye = get_vector(eye, p2);
    double d = dot_product(to_eye, normal);
    return d;
}
void print_vector(vector v1) {
    printf("Vector (%f, %f, %f)\n", v1.x, v1.y, v1.z);
}
