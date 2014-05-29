#include "line.h"
/*
int main(int argc, char ** argv) {
    init_background( "line.ppm" );
    int cols[3];
    cols[0] = 255;
    cols[1] = 255;
    cols[2] = 255;
    //draw_line(0, 0, 400, 400, cols);
    //draw_line(40, 0, 10, 100, cols);
    //draw_line(4, 5, 6, 7, cols);
    draw_line(90, 40, 50, 90, cols);
    draw_line(200, 12, 200, 400, cols);

}
**/
void draw_line_d(double x1, double y1, double x2, double y2, Uint32 col) {
    int X1 = x1;
    int Y1 = y1;
    int X2 = x2;
    int Y2 = y2;
    draw_line(X1, Y1, X2, Y2, col);
}
void draw_line(int x1, int y1, int x2, int y2, Uint32 color) {
    int xdiff = x1 - x2;
    int ydiff = y1 - y2;

    if( !xdiff && !ydiff ) {
        //Given only one point
        //color_pixel(x1, y1, cols);
        drawPixel(x1, y1, *(Uint32*)&color);
        return;
    }
    //Pick major direction
    int major = XMAJOR;
    if( abs(ydiff) > abs(xdiff) ) major = YMAJOR;
    //Swap the points if the major direction goes decrementally
    if( (major == XMAJOR) ? xdiff > 0 : ydiff > 0 ) {
        swap(x1, x2);
        swap(y1, y2);
    }
    //Color pixels
    int max = (major == XMAJOR) ? ( x2 - x1 ) : (y2 - y1);
    int min = (major != XMAJOR) ? ( x2 - x1 ) : (y2 - y1);
    int acc = 0;
    int inc = ( min < 0 ) ? -1 : 1;
    //printf("x1 x2 y1 y2 dirr%d %d %d %d %d\n", x1, x2, y1, y2, (major == XMAJOR));
    while( (major == XMAJOR) ? x1 <= x2 : y1 <= y2 ) {

        drawPixel(x1, y1, *(Uint32*)&color);
        acc += abs(min);
        if(acc >= max) {
            acc = acc % max;
            if(major == XMAJOR) y1 += inc; 
            else x1 += inc;
        }
        if(major == XMAJOR) x1++; 
        else y1++;

    }
}
/*
void color_pixel(int x, int y) {
    printf("Coloring pixel (x, y) : %d %d\n", x, y);
}*/
void draw_line_file_d(double x1, double y1, double x2, double y2, Uint32 col) {
    int X1 = x1;
    int Y1 = y1;
    int X2 = x2;
    int Y2 = y2;
    draw_line_file(X1, Y1, X2, Y2, col);
}
void draw_line_file(int x1, int y1, int x2, int y2, Uint32 color) {
    int xdiff = x1 - x2;
    int ydiff = y1 - y2;

    if( !xdiff && !ydiff ) {
        //Given only one point
        //color_pixel(x1, y1, cols);
        color_pixel_for_file(x1, y1, *(Uint32*)&color);
        return;
    }
    //Pick major direction
    int major = XMAJOR;
    if( abs(ydiff) > abs(xdiff) ) major = YMAJOR;
    //Swap the points if the major direction goes decrementally
    if( (major == XMAJOR) ? xdiff > 0 : ydiff > 0 ) {
        swap(x1, x2);
        swap(y1, y2);
    }
    //Color pixels
    int max = (major == XMAJOR) ? ( x2 - x1 ) : (y2 - y1);
    int min = (major != XMAJOR) ? ( x2 - x1 ) : (y2 - y1);
    int acc = 0;
    int inc = ( min < 0 ) ? -1 : 1;
    //printf("x1 x2 y1 y2 dirr%d %d %d %d %d\n", x1, x2, y1, y2, (major == XMAJOR));
    while( (major == XMAJOR) ? x1 <= x2 : y1 <= y2 ) {

        color_pixel_for_file(x1, y1, *(Uint32*)&color);
        acc += abs(min);
        if(acc >= max) {
            acc = acc % max;
            if(major == XMAJOR) y1 += inc; 
            else x1 += inc;
        }
        if(major == XMAJOR) x1++; 
        else y1++;

    }
}

