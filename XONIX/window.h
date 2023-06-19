#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <SDL.h>
#include <SDL_ttf.h>

#define WIN_WIDTH 1200
#define WIN_HEIGHT 1000
#define RECORDS_OFFSET 100

extern SDL_Window* window;
extern SDL_Renderer* ren;

void DeInitSDL(int error);

void InitSDL();

void InitFont(TTF_Font*& font);

#endif