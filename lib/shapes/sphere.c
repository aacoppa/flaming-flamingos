#include "sphere.h"

void draw_sphere(double x, double y, double z, double r, matrix * to_render) {
    struct point ** points = get_sphere_points(x, y, z, r);
    draw_triangles_in_sphere(points, to_render);
    free_points(points);
}
struct point ** get_sphere_points( double x, double y, double z, double r ) {
    double phi, theta;
    struct point ** points = malloc( (N_POINTS + 1) * sizeof( struct point *) );
    int i, j;
    i = 0;
    for( phi = 0; phi <= M_PI + .01; phi += (M_PI / N_POINTS)) {
        points[i] = malloc(sizeof( struct point ) * (N_POINTS + 1));
        j = 0;
        for( theta = 0; theta <= 2 * M_PI + .01; theta += 2 * M_PI / N_POINTS) {
            //points[i][j] = malloc(sizeof( struct point ));
            //Make the points going around and connect them
            points[i][j].x = x + r * sin( phi ) * cos( theta );
            points[i][j].y = y + r * sin( phi ) * sin( theta );
            points[i][j].z = z + r * cos( phi );
            //Connect the point to the last one
            j++;
        }
        i++;
    }
    return points;
}

void draw_triangles_in_sphere( struct point ** points, matrix * to_render ) {
    int i, j;
    for( i = 1; i <= N_POINTS; i++) {
        //I is travelling vertically...
        for( j = 1; j <= N_POINTS; j++) {
                struct point p1 = points[i - 1][j];
                struct point p2 = points[i - 1][j - 1];
                struct point p3 = points[i][j];
                struct point p4 = points[i][j-1];
                if(i != 1) {
                add_triangle_to_render(p3.x, p3.y, p3.z,
                                       p1.x, p1.y, p1.z,
                                       p4.x, p4.y, p4.z,
                                       to_render);
                add_triangle_to_render(p4.x, p4.y, p4.z,
                                         p1.x, p1.y, p1.z,
                                         p2.x, p2.y, p2.z,
                                         to_render);

                } else {
                add_triangle_to_render(p1.x, p1.y, p1.z,
                                       p3.x, p3.y, p3.z,
                                       p4.x, p4.y, p4.z,
                                       to_render);
                add_triangle_to_render(p1.x, p1.y, p1.z,
                                         p4.x, p4.y, p4.z,
                                         p2.x, p2.y, p2.z,
                                         to_render);
                }
        }
    }
    /*for(i = 1; i < N_POINTS; i++) {
        struct point p1 = points[i][0];
        struct point p2 = points[i][N_POINTS-1];
        struct point p3 = points[i-1][0];
        struct point p4 = points[i-1][N_POINTS-1];
        add_triangle_to_render(p1.x, p1.y, p1.z,
                p3.x, p3.y, p3.z,
                p4.x, p4.y, p4.z,
                to_render);

        add_triangle_to_render(p1.x, p1.y, p1.z,
                p4.x, p4.y, p4.z,
                p2.x, p2.y, p2.z,
                to_render);
    }
    for(i = 1; i < N_POINTS; i++) {
        struct point p1 = points[N_POINTS][i];
        struct point p2 = points[N_POINTS-1][i];
        struct point p3 = points[N_POINTS][i-1];
        struct point p4 = points[N_POINTS-1][i-1];
        add_triangle_to_render(p1.x, p1.y, p1.z,
                p3.x, p3.y, p3.z,
                p4.x, p4.y, p4.z,
                to_render);

        add_triangle_to_render(p1.x, p1.y, p1.z,
               p4.x, p4.y, p4.z,
                p2.x, p2.y, p2.z,
                to_render);
    }*/
}

void free_points(struct point ** points) {
    int i;
    i = 0;
    while(i <= N_POINTS) {
        free(points[i]);
        i++;
    }
    free(points);
}
/*void add_line_to_edge( double a, double b, double c, double d, double e, double f ) {
    printf("Making one line:\n%f %f %f\n%f %f %f\n", a, b, c, d, e, f);
}*/
void print_point( struct point p ) {
    printf("Printing point: (x, y, z) (%f, %f, %f)\n",
            p.x, p.y, p.z);
}
