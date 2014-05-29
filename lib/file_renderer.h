/* Generates the ppm:
 * usage:
 *  init_background( width, height );
 *  //Draw a bunch of lines
 *  write_array( file_name );
 */
#ifndef __BACKGROUND_ACG
#define __BACKGROUND_ACG 1

#include <stdio.h>
#include <stdlib.h>     
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "matrix/matrix.h"
#include "matrix/vector.h"
#include "screen.h"
#include "shapes/line.h"

//#define WIDTH 500
//#define HEIGHT 500

#define BYTES_PER_COLOR 16

#define START_BYTES 15
#define BYTES_PER_LINE ( BYTES_PER_COLOR * WIDTH + 1 )

void color_pixel_for_file(int, int, Uint32); 
int * random_colors();
void init_background();
void write_array( char * );
void clear_background();
void draw_triangles_to_file(matrix *, struct point, Uint32);
int fd;
int width, height; 
typedef struct color {
    int cols[3];
} color;

color ** pixels;
#endif
