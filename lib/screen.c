/*
 *  Description:
 *      screen.c is a minimalist wrapper for the SDL graphics library. The file
 *      contains functions for initializing and quitting a screen, plotting
 *      single pixels, and saving a given frame to a file.
 *
 *  Use:
 *      To include screen.c in your project:
 *
 *      1. download and install SDL:
 *          `sudo apt-get install libsdl1.2-dev libsdl-image1.2-dev \
 *          libsdl-mixer1.2-dev libsdl-ttf2.0-dev`
 *
 *      2. #include "screen.h" in your source
 *
 *      3. you must compile screen.c with the special flags displayed by the
 *          following terminal command:
 *          `sdl-config --libs --cflags`
 *
 *          Your makefile might have a target that look like this:
 *              screen.o: screen.c
 *                  $(CC) -o $@ -c $^ $(shell sdl-config --cflags --libs)
 *
 *      4. You must first initialize the screen with configureScreen().
 *          You may then plot points with drawPixel(); to display them, you call
 *          renderScreen() (which must be called whenever you want to display an
 *          updated screen -- ie, newly plotted pixels won't appear until the
 *          function call is made). Clear the screen with clearScreen(), and,
 *          once you're finished using it, call quitScreen().
 *
 *  Maintainer:
 *      Questions? Bugs?
 *      
 *      severyn.kozak@gmail.com
 *          
 */

#include "screen.h"

// necessary delay between the quitScreen() call and the time the screen quits
#define QUIT_DELAY 400
#define SCREEN_NAME "Graphics Engine: Screen"

static SDL_Surface * screen;
int image_width, image_height;
// initialize and configure the screen
void configureScreen(int w, int h){
    image_width = w;
    image_height = h;
    if((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1)){
        printf("Could not initialize SDL: %s.\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    screen = SDL_SetVideoMode(image_width, image_height, 32, SDL_SWSURFACE);
    SDL_WM_SetCaption(SCREEN_NAME, NULL);
}

// plot pixel (x, y) to the screen
void drawPixel(int x, int y, Uint32 pixel) {

    // check bounds
    if(x < 0 || image_width - 1 < x || y < 0 || image_height - 1 < y)
        return;

    Uint8 * pixelAddress = (Uint8 * )screen->pixels + y * screen->pitch +
        x * screen->format->BytesPerPixel;
    *(Uint32 *)pixelAddress = pixel;
}

// render screen, after new pixels have been plotted
void renderScreen(){
    SDL_Flip(screen);
}

// clear the screen by filling it with black pixels
void clearScreen(){
    SDL_FillRect(screen, NULL, 0x000000);
}

// close the screen and perform memory cleanup
void quitScreen(){
    SDL_Delay(QUIT_DELAY);
    SDL_Quit();
}

// write the screen's pixels matrix to a BMP file named filename
int writeScreen(const char * const filename){
    return SDL_SaveBMP(screen, filename);
}
