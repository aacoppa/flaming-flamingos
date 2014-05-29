/*      LINE-DRAWING ALGORITHM
 *      usage:
 *          draw_line( x1, y1, x2, y2, colors );
 *          // Calls backgrounds color_pixel (just colors one of the pixels in pixel array)
 */
#ifndef __LINE_ACG
#define __LINE_ACG 1
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "../screen.h" //Screen pixel drawing
#include "../file_renderer.h" //File pixel drawing

//#define WIDTH 500
//#define HEIGHT 500

#define XMAJOR 0
#define YMAJOR 1

//Integers only please
#define swap(x,y) { x = x + y; y = x - y; x = x - y; }

void draw_line_d(double, double, double, double, Uint32);
void draw_line(int, int, int, int, Uint32); 
void draw_line_file_d(double, double, double, double, Uint32);
void draw_line_file(int, int, int, int, Uint32); 

#endif
