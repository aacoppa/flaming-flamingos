#pragma once
#include <SDL/SDL.h>
#include <float.h>
#include "world.h"

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

zbuff *** zbuffer;
