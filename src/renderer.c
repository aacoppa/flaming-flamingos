#include "renderer.h"

/* Initializes the screen: to be called once 
 * width & height in pixels, s numbers are screen corners
 */
void init_screen(double SXL, double SYL, double SXR, double SYR, int w, int h) {
    sxr = SXR;
    syr = SYR;
    sxl = SXL;
    syl = SYL;
    configureScreen(w, h);
    width = w;
    height = h;
}
/* Start the drawing process:
 * render matrix to_render to the eye given
 */
void draw_to_screen(double ex, double ey, double ez, matrix * to_render, Uint32 color) {
    clearScreen();
    convert_to_eye_coordinates(ex, ey, ez, &to_render);
    struct point eye;
    eye.x = ex;
    eye.y = ey;
    eye.z = ez;
    draw_triangles(to_render, eye, color);
    renderScreen();
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

void convert_to_eye_coordinates( double ex, double ey, double ez, matrix ** to_render_orig) {
    matrix * to_render = *to_render_orig;
    int i, curr_column;
    matrix * temp = malloc(sizeof(matrix));
    *temp = init_matrix(to_render->width, 4);
    curr_column = 4;
    for( i = 4; i < to_render->width; i++ ) {
        
        to_render->mat[i][0] = (-ez / (to_render->mat[i][2] - ez) ) * ( to_render->mat[i][0] - ex) + ex;
        to_render->mat[i][1] = (-ez / (to_render->mat[i][2] - ez) ) * ( to_render->mat[i][1] - ey) + ey;
        temp->mat[i][0] = (width)  * (to_render->mat[i][0] - sxl) / (sxr - sxl);
        temp->mat[i][1] = height - ( (height) * (to_render->mat[i][1] - syl) / (syr - syl) );
        curr_column++;
    }
    delete_matrix(*to_render);
    *to_render_orig = temp;
}

void convert_from_screen(matrix * to_render) {
    int i;
    for( i = 4; i < to_render->width; i++ ) {
        to_render->mat[i][0] = (width)  * (to_render->mat[i][0] - sxl) / (sxr - sxl); 
        to_render->mat[i][1] = height - ( (height) * (to_render->mat[i][1] - syl) / (syr - syl) );
    }
}

void draw_triangles(matrix * to_render, struct point eye, Uint32 color){
    int startX = 6; //Start at 6 because our matrix begins with 4 
                    //Empty slots
    struct point p1, p2, p3;
    /* Loop through the matrix, going through each triangle
     * one by one
     */
    while( startX < to_render->width ) {
        p1.x = to_render->mat[startX-2][0];
        p1.y = to_render->mat[startX-2][1];
        p1.z = to_render->mat[startX-2][2];
        p2.x = to_render->mat[startX-1][0];
        p2.y = to_render->mat[startX-1][1];
        p2.z = to_render->mat[startX-1][2];
        p3.x = to_render->mat[startX][0];
        p3.y = to_render->mat[startX][1];
        p3.z = to_render->mat[startX][2];
        /* These are ordered counter-clockwise from when they are inserted
         */
        if(get_direction(p1, p2, p3, eye) < 0) {
            //Thus we can cull right here
            startX += 3;
            continue;
        }
        //Draw the three lines
        //

        draw_line_d( to_render->mat[startX - 2][0], to_render->mat[startX - 2][1],
                to_render->mat[startX - 2][2], to_render->mat[startX - 1][0], 
                to_render->mat[startX - 1][1], to_render->mat[startX - 1][2],
                *(Uint32 *)&color);
        draw_line_d( to_render->mat[startX - 2][0], to_render->mat[startX - 2][1],
                to_render->mat[startX - 2][2], to_render->mat[startX][0], 
                to_render->mat[startX][1], to_render->mat[startX][2],
                *(Uint32 *)&color);
        draw_line_d( to_render->mat[startX-1][0], to_render->mat[startX - 1][1],
                to_render->mat[startX - 1][2], to_render->mat[startX][0], 
                to_render->mat[startX][1], to_render->mat[startX][2],
                *(Uint32 *)&color);
        /* If we want to fill this triangle then...
         * get a matrix of lines to be drawn by calling fill triangle
         */
        matrix * m = fill_triangle( p1, p2, p3);
        int p = 0;
        /* Then just loop through the matrix drawing a line for every two
         * columns (one column represents one endpoint)
         */
        while(p < m->width) {
            draw_line_d(m->mat[p][0], m->mat[p][1], m->mat[p][2],
                        m->mat[p+1][0], m->mat[p+1][1], m->mat[p+1][2],
                        *(Uint32 *)&color);
            p += 2;
        }
        //End of filling
        startX += 3;
    }
}


