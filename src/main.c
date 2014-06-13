#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "renderer.h"
#include "shapes/box.h"
#include "shapes/sphere.h"
#include "world.h"

int render_test();
int main(int argc, char ** argv) {
    init_world();
    while(1) { 
        go();
    }
    return 0;
}
