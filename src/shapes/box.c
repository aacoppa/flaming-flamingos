#include "box.h"
void draw_box_given_transforms(double sx, double sy, double sz,
                               double rx, double ry, double rz,
                               double mx, double my, double mz,
                               matrix * to_render) {
    draw_box(1, 1, 1, 0, 0, 0, to_render);
    double ss[3];
    ss[0] = sx;
    ss[1] = sy;
    ss[2] = sz;
    double ms[3];
    ms[0] = mx;
    ms[1] = my;
    ms[2] = mz;
    matrix transformer = init_identity(4);
    if(rx) multiply_matrix_onto_self( rotation_matrix_x(rx), &transformer);
    if(ry) multiply_matrix_onto_self( rotation_matrix_y(ry), &transformer);
    if(rz) multiply_matrix_onto_self( rotation_matrix_z(rz), &transformer);
    if( (sx!=1) || (sy!=1) || (sz!=1) ) multiply_matrix_onto_self( scale_matrix(ss), &transformer);
    if(mx || my || mz) multiply_matrix_onto_self( translation_matrix(ms), &transformer);

}
void draw_box(double w, double h, double d, double x, double y, double z, matrix * to_render) {
    struct face * faces = get_box_faces(w, h, d, x, y, z);
    draw_triangles_in_box(faces, to_render);
    free_faces(faces);
}
struct face * get_box_faces(double width, double height, double depth,
                          double x, double y, double z) {
    struct face * faces = malloc(6 * sizeof(struct face));
    double left_corner_x = x - width / 2;
    int i, j;
    faces[0].points = malloc(N_DIVISIONS * sizeof(struct point *));
    double increment_x = x - width / 2;
    double increment_y = y - height / 2;
    double increment_z = z - depth / 2;
    for(i = 0; i < 6; i++) faces[i].points = malloc(N_DIVISIONS * sizeof(struct point *));
    for(i = 0; i < N_DIVISIONS; i++) {
        increment_y = y - height / 2;
        faces[0].points[i] = malloc(N_DIVISIONS * sizeof(struct point));
        faces[1].points[i] = malloc(N_DIVISIONS * sizeof(struct point));
        for(j = 0; j < N_DIVISIONS; j++) {
            faces[0].points[i][j].x = increment_x;
            faces[0].points[i][j].y = increment_y;
            faces[0].points[i][j].z = increment_z;

            faces[1].points[i][j].x = increment_x;
            faces[1].points[i][j].y = increment_y;
            faces[1].points[i][j].z = increment_z + depth;

            increment_y = increment_y + height / (N_DIVISIONS - 1);
        }
        increment_x = increment_x + width / (N_DIVISIONS - 1);
    }
    increment_x = x - width / 2;
    increment_y = y - height / 2;
    increment_z = z - depth / 2;
    for(i = 0; i < N_DIVISIONS; i++) {
        increment_z = z - depth / 2;
        faces[2].points[i] = malloc(N_DIVISIONS * sizeof(struct point));
        faces[3].points[i] = malloc(N_DIVISIONS * sizeof(struct point));

        for(j = 0; j < N_DIVISIONS; j++) {
        
            faces[2].points[i][j].x = increment_x;
            faces[2].points[i][j].y = increment_y;
            faces[2].points[i][j].z = increment_z;

            faces[3].points[i][j].x = increment_x + width;
            faces[3].points[i][j].y = increment_y;
            faces[3].points[i][j].z = increment_z;

            increment_z = increment_z + depth / (N_DIVISIONS - 1);
        }
        increment_y = increment_y + height / (N_DIVISIONS - 1);
    }

    increment_x = x - width / 2;
    increment_y = y - height / 2;
    increment_z = z - depth / 2;
    for(i = 0; i < N_DIVISIONS; i++) {
        increment_x = x - width / 2;
        faces[4].points[i] = malloc(N_DIVISIONS * sizeof(struct point));
        faces[5].points[i] = malloc(N_DIVISIONS * sizeof(struct point));

        for(j = 0; j < N_DIVISIONS; j++) {
            
            faces[4].points[i][j].x = increment_x;
            faces[4].points[i][j].y = increment_y;
            faces[4].points[i][j].z = increment_z;

            faces[5].points[i][j].x = increment_x;
            faces[5].points[i][j].y = increment_y + height;
            faces[5].points[i][j].z = increment_z;

            increment_x = increment_x + width / (N_DIVISIONS - 1);
        }
        increment_z = increment_z + depth / (N_DIVISIONS - 1);
    }
    return faces;
}

void draw_triangles_in_box( struct face * faces, matrix * to_render ) {
    int i, j, k;
    for(i = 0; i < 6; i++) {
        for(j = 1; j < N_DIVISIONS; j++) {
            for(k = 1; k < N_DIVISIONS; k++) {
                struct point p1 = faces[i].points[j - 1][k];
                struct point p2 = faces[i].points[j - 1][k - 1];
                struct point p3 = faces[i].points[j][k];
                struct point p4 = faces[i].points[j][k-1];
                if(i % 2 == 0) { //0 || i == 3 || i == 5) {
                    add_triangle_to_render(p4.x, p4.y, p4.z,
                            p1.x, p1.y, p1.z,
                            p3.x, p3.y, p3.z,
                            to_render);
                    add_triangle_to_render(p4.x, p4.y, p4.z,
                            p2.x, p2.y, p2.z,
                            p1.x, p1.y, p1.z,
                            to_render);
 
                } else {
                    add_triangle_to_render(p1.x, p1.y, p1.z,
                            p4.x, p4.y, p4.z,
                            p3.x, p3.y, p3.z,
                            to_render);
                    add_triangle_to_render(p2.x, p2.y, p2.z,
                            p4.x, p4.y, p4.z,
                            p1.x, p1.y, p1.z,
                            to_render);

                   
                    // add_triangle_to_render(p1.x, p1.y, p1.z,
                   //         p3.x, p3.y, p3.z,
                   //         p2.x, p2.y, p2.z,
                   //         to_render);
                   // add_triangle_to_render(p4.x, p4.y, p4.z,
                   //         p3.x, p3.y, p3.z,
                   //         p2.x, p2.y, p2.z,
                   //         to_render);

                }
            }
        }
    }
}
void free_faces(struct face * faces) {
    int i = 0;
    while(i < 6) {
        int j = 0;
        while( j < N_DIVISIONS ) {
            free(faces[i].points[j]);
            j++;
        }
        free(faces[i].points);
        i++;
    }
    free(faces);
}
