#include "transformations.h"

matrix scale_matrix( double ss [] ) {
    matrix ret = init_identity( 4 );
    set_element( ret, ss[0], 0, 0 );
    set_element( ret, ss[1], 1, 1 );
    set_element( ret, ss[2], 2, 2 );
    return ret;
}

matrix translation_matrix( double ts[] ) {
    matrix ret = init_identity( 4 );
    set_element( ret, ts[0], 3, 0 );
    set_element( ret, ts[1], 3, 1 );
    set_element( ret, ts[2], 3, 2 );
    return ret;
}

matrix rotation_matrix_x( double theta ) {
    matrix ret = init_identity( 4 );
    set_element( ret, cos(theta), 1, 1);
    set_element( ret, -sin(theta), 2, 1);
    set_element( ret, sin(theta), 1, 2);
    set_element( ret, cos(theta), 2, 2);
    return ret;
}

matrix rotation_matrix_y( double theta ) {
    matrix ret = init_identity( 4 );
    set_element( ret, cos(theta), 0, 0);
    set_element( ret, sin(theta), 2, 0);
    set_element( ret, -sin(theta), 0, 2);
    set_element( ret, cos(theta), 2, 2);
    return ret;
}

matrix rotation_matrix_z( double theta ) {
    matrix ret = init_identity( 4 );
    set_element( ret, cos(theta), 0, 0);
    set_element( ret, -sin(theta), 1, 0);
    set_element( ret, sin(theta), 0, 1);
    set_element( ret, cos(theta), 1, 1);
    return ret;
}
