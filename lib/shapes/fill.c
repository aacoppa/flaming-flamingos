#include "fill.h"
/* Fill triangles with scan-line conversion
 * Lots' o cases
 * -top is flat, bottom is flat, no height at all
 * 1) order points
 * lets say a, b, c is the order from top to bottom
 * 2) find slope of ab and ac: traverse down incrementing a t value and drawing horizontal lines
 * 3) find slope of ac and bc: traverse down incrementing a t value and drawing horizontal lines
 *
 */

int fill_test()
{
    struct point p1;
    p1.y = 100;
    p1.x = 100;

    struct point p2;
    p2.y = 90;
    p2.x = 910;

    struct point p3;
    p3.y = 90;
    p3.x = 95;
    matrix * m = malloc(sizeof(matrix));
    *m = init_matrix(0, 0);
    draw_top(p1, p2, p3, m);
    return 0;
}
void add_line(int x1, int y1, int x2, int y2, matrix * m) {

    matrix p = add_columns(*m, 2);
    *m = p;
    //printf("%d %d w h\n", m->width, m->height);
    m->mat[m->width-2][0] = x1;
    m->mat[m->width-2][1] = y1;
    m->mat[m->width-2][2] = 0;
    m->mat[m->width-2][3] = 1;
    m->mat[m->width-1][0] = x2;
    m->mat[m->width-1][1] = y2;
    m->mat[m->width-1][2] = 0;
    m->mat[m->width-1][3] = 1;
}
void add_line_p(struct point p1, struct point p2, matrix * m) {
    /* Add line to the matrix that will later be rendered
     */
    *m = add_columns(*m, 2);
    m->mat[m->width-2][0] = p1.x;
    m->mat[m->width-2][1] = p1.y;
    m->mat[m->width-2][2] = 0;
    m->mat[m->width-2][3] = 1;
    m->mat[m->width-1][0] = p2.x;
    m->mat[m->width-1][1] = p2.y;
    m->mat[m->width-1][2] = 0;
    m->mat[m->width-1][3] = 1;
}


int special_case(struct point p1, struct point p2, 
                   struct point p3, matrix * lines) {
    /* Checks if we're given not a triangle;
     * handles the cases that come up if thats the case
     */
    if(p1.y == p2.y && p2.y == p3.y) {
        add_line_p(p1, p3, lines);
        add_line_p(p2, p3, lines);
        return 0;
    }
    if(p1.y == p2.y) return BOTTOM_TRIANGLE;
    if(p2.y == p3.y) return TOP_TRIANGLE;
    return BOTH;
}

matrix * fill_triangle(struct point pa, struct point pb, struct point pc) {
    /* Cases to handle:
     *  1) not_a_triangle
     *  
     */
    matrix * m = malloc(sizeof(matrix));
    *m = init_matrix(0, 4);
    //Order the points
    struct point p1, p2, p3;
    if(pa.y > pb.y) {
        if(pb.y > pc.y) {
            p1 = pa;
            p2 = pb;
            p3 = pc;
        } else {
            p3 = pb;
            if(pa.y > pc.y) {
                p1 = pa;
                p2 = pc;
            } else {
                p1 = pc;
                p2 = pa;
            }
        }
    } else {
        if(pc.y > pb.y) {
            p3 = pa;
            p1 = pc;
            p2 = pb;
        } else {
            p1 = pb;
            if(pc.y > pa.y) {
                p2 = pc;
                p3 = pa;
            } else {
                p2 = pa;
                p3 = pc;
            }
        }
    }
    int c = special_case(p1, p2, p3, m);
    if(!c) return m;
    if(c == TOP_TRIANGLE || c == BOTH) {
        draw_top(p1, p2, p3, m);
    }
    if(c == BOTTOM_TRIANGLE || c == BOTH) {
        //Find the point on the line between p1 and p3
        float ratio = (p1.x - p3.x) / (p1.y - p3.y);
        struct point new_p;
        new_p.y = p2.y;
        new_p.x = ratio * (new_p.y -p3.y) + p3.x;
        //Swap the order of the points
        draw_bottom(p3, p2, new_p, m);
    }
    add_line_p(p1, p3, m);
    add_line_p(p2, p3, m);
    add_line_p(p1, p2, m);
    return m;
}

void draw_top(struct point p1, struct point p2, struct point p3, matrix * lines) {
    int y_curr = p1.y-1;
    struct point pr = (p2.x > p3.x) ? p2 : p3;
    struct point pl = (p2.x <= p3.x) ? p2 : p3;
    int x_diff_r = abs(p1.x - pr.x);
    int y_diff_r = abs(p1.y - pr.y);
    int inc_r = (p1.x > pr.x) ? -1 : 1;
    if(!x_diff_r) inc_r = 0;
    int acc_r = 0;
    int x_r, x_l;
    x_r = x_l = p1.x;
    int x_diff_l = abs(p1.x - pl.x);
    int y_diff_l = abs(p1.y - pl.y);
    int inc_l = (p1.x > pl.x) ? -1 : 1;
    if(!x_diff_l) inc_l = 0;
    int acc_l = 0;
    while(y_curr >= p2.y) {
        acc_r += x_diff_r;
        while(acc_r >= y_diff_r) {
            acc_r -= y_diff_r;
            x_r += inc_r;
        }
        acc_l += x_diff_l;
        while(acc_l >= y_diff_l) {
            acc_l -= y_diff_l;
            x_l += inc_l;
        }
        //printf("x1, x2, y, %d, %d, %d\n", x_l, x_r, y_curr);
        add_line(x_l, y_curr, x_r, y_curr, lines);
        y_curr--;
    }
}

void draw_bottom(struct point p1, struct point p2, struct point p3, matrix * lines) {
    int y_curr = p1.y+1;
    struct point pr = (p2.x > p3.x) ? p2 : p3;
    struct point pl = (p2.x <= p3.x) ? p2 : p3;
    int x_diff_r = abs(p1.x - pr.x);
    int y_diff_r = abs(p1.y - pr.y);
    int inc_r = (p1.x > pr.x) ? -1 : 1;
    int acc_r = 0;
    int x_r, x_l;
    x_r = x_l = p1.x;
    int x_diff_l = abs(p1.x - pl.x);
    int y_diff_l = abs(p1.y - pl.y);
    int inc_l = (p1.x > pl.x) ? -1 : 1;
    if(!x_diff_l) inc_l = 0;
    int acc_l = 0;
    while(y_curr <= p2.y) {
        acc_r += x_diff_r;
        while(acc_r >= y_diff_r) {
            acc_r -= y_diff_r;
            x_r += inc_r;
        }
        acc_l += x_diff_l;
        while(acc_l >= y_diff_l) {
            acc_l -= y_diff_l;
            x_l += inc_l;
        }
        //printf("x1, x2, y, %d, %d, %d\n", x_l, x_r, y_curr);
        add_line(x_l, y_curr, x_r, y_curr, lines);
        y_curr++;
    }
}
