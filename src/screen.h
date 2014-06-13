#pragma once
#include <SDL/SDL.h>
#include <float.h>
#include "eye.h"
void configureScreen();
void drawPixel(int x, int y, Uint32 pixel);
void addPixelToBuffer(int x, int y, double z, Uint32 pixel);
void renderScreen();
void clearScreen();
void quitScreen();
int writeScreen(const char * const filename);

typedef struct zbuff {
    double z;
    Uint32 color;
} zbuff;

Uint32 red;
Uint32 blue;
Uint32 green;
Uint32 black;
Uint32 white;
zbuff *** zbuffer;
