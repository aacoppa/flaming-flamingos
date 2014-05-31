#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "renderer.h"
#include "interpret.h"

matrix * m;
int render_test();
int main(int argc, char ** argv) {
    //m = import_object("teapot.3dt");
    if(argc < 2) {
        return render_test();
    } else return read_file(argv[1]);
}

int render_test() {
    init_screen(-2, -2, 2, 2, 500, 500);
    float theta = M_PI / 3;
    struct timeval start, end;
    long mtime, secs, usecs;    
    int i = 0;
    matrix edge = init_identity(4);
    eye.x = 0;
    eye.y = 5;
    eye.z = 10;
    //draw_box(1, 1, 1, 1, 0, 0, &edge);
    draw_sphere(-1, 0, 0, 1, &edge);
    SDL_Color s;
    s.r = 0;
    s.g = 0;
    s.b = 255;
    float total_frames = 0;
    gettimeofday(&start, NULL);
    while( i < 300 ) {
    theta = theta + M_PI / 30;
    matrix transformer = init_identity( 4 );
    //multiply_matrix_onto_self(rotation_matrix_x(theta), &transformer);
    multiply_matrix_onto_self(rotation_matrix_z(theta), &transformer);
    multiply_matrix_onto_self(rotation_matrix_y(theta), &transformer);
    double s[3];
    s[0] =.4;
    s[1] =.4;
    s[2] =.4;
    multiply_matrix_onto_self(scale_matrix(s), &transformer);
    matrix to_render = multiply_matrix(transformer, edge);
    draw_to_screen(eye.x, eye.y, eye.z, &to_render, *(Uint32 *)&s);
    SDL_Delay(100);

    //printf("y: %f\n", eye.y);
    //eye.y -= .01;
        //printf("Or %f seconds\n", l);
    total_frames++;
    //printf("Frames per sec: %f\n", l);
    //1 / framerate = 1000 * millseconds
    //ez = ez + 1;*/
    i++;
    }
    gettimeofday(&end, NULL);
    secs  = end.tv_sec  - start.tv_sec;
    usecs = end.tv_usec - start.tv_usec;
    mtime = ((secs) * 1000 + usecs/1000.0) + 0.5;
    //printf("Elapsed time: %ld millisecs\n", mtime);
    double l = (double) mtime / 1000;

    printf("Total frames: %f\n", total_frames);
    printf("Total time: %f\n", l);
    printf("Average fps: %f\n", total_frames / l);
    return 0;
}
