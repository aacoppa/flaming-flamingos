#include "import.h"
/* Imports objects from .3dt data files
 * for rendering
 *
 */
matrix * import_object(char * fn) {
    char ** args;
    char buffer[1001];
    matrix * m = malloc(sizeof(matrix));
    *m = init_matrix(4, 4);
    assert(fn);
    FILE * fp = fopen(fn, "r");
    int lines = 0;
    int curr = 7;
    while( 1 ) {
        fgets(buffer, 1000, fp);
        //printf("Buff: %s\n", buffer);
        args = parse_split(buffer);
        int z = 0;
        while( args[z] ) {
            //printf("%d : %s\n", z, args[z]);
            z++;
        }
        if(!args[0]) return m;
        if(args[0][0] == '#') continue;
        if(lines == 0) {
            lines = atoi(args[0]);
            *m = add_columns(*m, lines*3);
            continue;
        }
        int i = 0;
        int j = 3;
        while(i < 9) {
            double v1 = strtod(args[i], NULL);
            double v2 = strtod(args[i+1], NULL);
            double v3 = strtod(args[i+2], NULL);
         //   printf("%d\n", curr-j);
            m->mat[curr-j][0] = v1;
            m->mat[curr-j][1] = v2;
            m->mat[curr-j][2] = v3;
            m->mat[curr-j][3] = 1;
            i+=3;
            j--;
        }
        buffer[0] = NULL;
        curr += 3;
    }
    return m;
}
