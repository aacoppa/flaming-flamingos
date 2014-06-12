#include "matrix.h"

matrix init_identity( int L ) {
    matrix m = init_matrix( L, L );
    fill_matrix(m , 0);
    int i = 0;
    while( i < m.width ) {
        m.mat[i][i] = 1;
        i++;
    }
    return m;
}
void set_element(matrix m, double value, int x, int y) {
    if( x < 0 || x >= m.width || y < 0 || y > m.height) {
        fprintf(stderr, "Error: Coordinates (x, y) (%d, %d) are out of bounds\n", x, y);
        return;
    }
    m.mat[x][y] = value;
}
void fill_matrix( matrix m, double val ) {
    int i, j;
    for(i = 0; i < m.width; i++) {
        for(j = 0; j < m.height; j++) m.mat[i][j] = val;
    }
}
matrix init_matrix(int width, int height) {
    matrix m;
    m.mat = malloc( sizeof(double *) * width );
    int i, j;
    for(i = 0; i < width; i++) {
        m.mat[i] = malloc(sizeof(double) * height);
        for( j = 0; j < height; j++) {
            m.mat[i][j] = 1; 
        }
    }
    m.width = width;
    m.height = height;
    return m;
}
void scalar_multiply(double S, matrix m) {
    int i, j;
    for(i = 0; i < m.height; i++) 
        for(j = 0; j < m.width; j++) 
            m.mat[i][j] *= S;
}
matrix multiply_matrix(matrix a, matrix b) {
    if( a.width != b.height ) {
        fprintf(stderr, "Error: Matrixes of [%d x %d], [%d x %d] cannot be multiplied\n", a.width, a.height, b.width, b.height);
        matrix m;
        return m; 
    }
    
    double ** ret = malloc( sizeof(double *) * b.width );
    int i;
    for(i = 0; i < b.width; i++) {
        ret[i] = malloc(sizeof(double) * a.height);
    }
    int ay, bx;
    ay = bx = 0;
    while( ay < a.height ) {
        while( bx < b.width ) {
            //Set current row
            ret[bx][ay] = col_x_row( b.mat[bx], a, ay );
            bx++;
        }
        ay++;
        bx = 0;
    }

    matrix m;
    m.width = b.width;
    m.height = a.height;
    m.mat = ret;
    return m;
}

double col_x_row( double * col, matrix a, int r_num ) {
    int i;
    double ret = 0;
    i = 0;
    while( i < a.width ) {
        ret += (a.mat[i][r_num] * col[i]);
        i++;
    }
    return ret;
}

void print_matrix(matrix m) {
    int i, j;
    for(i = 0; i < m.height; i++) {
        for(j = 0; j < m.width; j++) {
            printf("%f\t", m.mat[j][i]);
        }
        printf("\n");
    }
    printf("\n\n");
}

void delete_matrix(matrix m) {
    int i;
    for(i = 0; i < m.width; i++) {
        if(m.mat[i] != NULL) free(m.mat[i]);
    }
    free(m.mat);
}
matrix add_column(matrix a) {
    matrix b = init_matrix( a.width + 1, a.height);
    int i, j;
    for(i = 0; i < a.width; i++) {
        for(j = 0; j < a.height; j++) {
            b.mat[i][j] = a.mat[i][j];
        }
    }
    delete_matrix(a);
    return b;
}
matrix add_columns( matrix a, int nCols ) {
    matrix b = init_matrix( a.width + nCols, a.height);
    int i, j;
    for(i = 0; i < a.width; i++) {
        for(j = 0; j < a.height; j++) {
            b.mat[i][j] = a.mat[i][j];
        }
    }
    delete_matrix(a);
    return b;
}
void combine_matrices(matrix * original, matrix * to_be_added) {
    original->mat = realloc(original->mat, sizeof(double *) * (original->width + to_be_added->width));
    int i = original->width;
    int j = 0;
    original->width = original->width + to_be_added->width;
    while(i < original->width) {
        original->mat[i] = to_be_added->mat[j];
        i++;
        j++;
    }
}
matrix copy_matrix( matrix m ) {
    matrix ret = init_matrix( m.width, m.height );
    int i, j;
    for( i = 0; i < ret.width; i++ ) {
        for( j = 0; j < ret.height; j++) {
            ret.mat[i][j] = m.mat[i][j];
        }
    }
    return ret;
}
void multiply_matrix_onto_self( matrix transformer, matrix * me) {
    matrix temp = multiply_matrix(transformer, *me);
    delete_matrix(*me);
    *me =  temp;
}
