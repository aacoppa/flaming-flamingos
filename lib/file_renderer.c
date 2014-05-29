#include "file_renderer.h"
void init_background(int w, int h) {
    width = w;
    height = h;
    pixels = malloc( width * sizeof(int *));
    int i;
    for(i = 0; i < width; i++) pixels[i] = malloc( height * sizeof(color) );
}
void write_to_file(char * fn) {
    //*(strchr(fn, '\n')) = '\0';
    //int p = 0;
    //for( p = 0; p < 30; p++ ) printf("%c\n", fn[p]);
    char * clean_fn = malloc( strlen(fn) + 1 );
    strcpy(clean_fn, fn);
    fd = open(clean_fn, O_CREAT | O_TRUNC | O_RDWR, 0666);
    char * header = malloc( 15 );
    strcat(header, "P3\n");
    char num[4];
    sprintf(num, "%d", width);
    strcat(header, num);
    strcat(header, " ");
    sprintf(num, "%d", height);
    strcat(header, num);
    strcat(header, " 255\n");
    write(fd, header, strlen(header));
    int i = 0;
    while( i < height ) {
        int j = 0;
        while( j < width ) {
            char * color = malloc(BYTES_PER_COLOR);
            int k;
            for(k = 0; k < 3; k++) {
                char c[4];
                sprintf(c, "%d", pixels[j][i].cols[k]);
                strcat(color, c);
                strcat(color, " ");
            }
            write(fd, color, BYTES_PER_COLOR);
            j++;
        }
        write(fd, "\n", 1);
        i++;
    }
    close(fd);
}
void draw_triangles_to_file(matrix * to_render, struct point eye, Uint32 color) {
    int startX = 6;
    if(to_render->width <= 4) return;

    struct point p1, p2, p3;
    while( startX < to_render->width ) {
        p1.x = to_render->mat[startX-2][0];
        p1.y = to_render->mat[startX-2][1];
        p1.z = to_render->mat[startX-2][2];
        p2.x = to_render->mat[startX-1][0];
        p2.x = to_render->mat[startX-1][1];
        p2.x = to_render->mat[startX-1][2];
        p3.x = to_render->mat[startX][0];
        p3.x = to_render->mat[startX][1];
        p3.x = to_render->mat[startX][2];
        if(get_direction(p1, p2, p3, eye) <= 0) {
            startX += 3;
            continue;
        }
        draw_line_file_d( to_render->mat[startX - 2][0], to_render->mat[startX - 2][1],
                to_render->mat[startX - 1][0], to_render->mat[startX - 1][1], *(Uint32 *)&color);
        draw_line_file_d( to_render->mat[startX - 2][0], to_render->mat[startX - 2][1],
                to_render->mat[startX][0], to_render->mat[startX][1], *(Uint32 *)&color);
        draw_line_file_d( to_render->mat[startX-1][0], to_render->mat[startX-1][1],
                to_render->mat[startX][0], to_render->mat[startX][1], *(Uint32 *)&color);
                
        startX += 3;
    }
}


void clear_background() {
    int i, j, k;
    for(i = 0; i < width; i++) {
        for(j = 0; j < height; j++) {
            for(k = 0; k < 3; k++) {
                pixels[i][j].cols[k] = 0;
            }
        }
    }
}
void color_pixel_for_file(int x, int y, Uint32 cols) {
    /*
    if( x >= width || x < 0 || y >= height || y < 0) return;
    int off = START_BYTES + y * BYTES_PER_LINE;
    off = off + x * BYTES_PER_COLOR;
    lseek(fd, off, SEEK_SET);
    char * out = malloc(BYTES_PER_COLOR);
    int k;
    for(k = 0; k < 3; k++) {
        char c[4];
        sprintf(c, "%d", cols[k]);
        strcat(out, c);
        strcat(out, " ");
    }
    write(fd, out, BYTES_PER_COLOR);
    */
    
    if( x < 0 || x >= width || y < 0 || y > height ) return;
    pixels[x][y].cols[0] = ((SDL_Color *)&cols)->r;
    pixels[x][y].cols[1] = ((SDL_Color *)&cols)->g;
    pixels[x][y].cols[2] = ((SDL_Color *)&cols)->b;
}
