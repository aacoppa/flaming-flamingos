#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "renderer.h"
#include "shapes/box.h"
#include "shapes/sphere.h"
#include "world.h"
matrix * m;
int render_test();
int main(int argc, char ** argv) {
    //m = import_object("teapot.3dt");
    if(argc < 2) {
        return render_test();
    }
    return 0;
}

int render_test() {
    init_screen(-2, -2, 2, 2, 500, 500);
    float theta = M_PI / 3;
    struct timeval start, end;
    long mtime, secs, usecs;
    int i = 0;
    SDL_Color s;
    s.r = 0;
    s.g = 0;
    s.b = 255;
    float total_frames = 0;
    gettimeofday(&start, NULL);
    init_world();
    add_object();
    while( i < 300 ) {
        go();
        SDL_Delay(5);

        total_frames++;
        i++;
        printf("hello\n");
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
