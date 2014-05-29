/*    TRANSFORMATIONS
 *    RETURNS A NEW MATRIX OF THE GIVEN TRANSFORMATION
 *
 *  
 */
#ifndef __TRANSFORMS_ASC
#define __TRANSFORMS_ASC 1

#include "math.h"
#include "matrix.h"
matrix scale_matrix( double []);
matrix rotation_matrix_x( double theta );
matrix rotation_matrix_y( double theta );
matrix rotation_matrix_z( double theta );
matrix translation_matrix( double [] );


/*
 * Connect eye to world space, where it crosses screen you
 * draw point
 */
#endif
