#ifndef __INTERP_ACG
#define __INTERP_ACG 1

#include <stdio.h>
#include <stdlib.h>     
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "parse_util.h"
#include "matrix/transformations.h"
#include "assert.h"
#include "shapes/sphere.h"
#include "shapes/box.h"
#include "file_renderer.h"

#define COLOR           1
#define LINE            2
#define NAME            3
#define QUIT            4
#define NOT_READY       5
#define ERROR           6
#define COMMENT         7
#define ROTATE_X        8
#define ROTATE_Y        9
#define ROTATE_Z        10
#define TRANSLATE       11
#define SCALE           12
#define SCREEN          13
#define PIXELS          14    
#define TRANSFORM       15
#define RENDER_PARALLEL 16
#define RENDER_CYCLOPS  17
#define RENDER_STEREO   18
#define IDENTITY        19
#define CLEAR_PIXELS    20
#define CLEAR_EDGES     21
#define SPHERE          22
#define BOX             23

FILE * fp;
int * curr_cols;
char ** args;
matrix interpret_renderer;
matrix transformer;

void init(char *);
int read_file(char *);
int next_type();
int handle_type();
char * next_data();
int * get_points();
double convert_to_radians(double);
#endif
