#pragma once
#include <SDL/SDL.h>

void configureScreen();
void drawPixel(int x, int y, Uint32 pixel);
void renderScreen();
void clearScreen();
void quitScreen();
int writeScreen(const char * const filename);
