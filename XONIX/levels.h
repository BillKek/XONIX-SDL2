#ifndef _LEVELS_H_
#define _LEVELS_H_

#include "game.h"
#include "menu.h"

bool menu(SDL_Window* window, SDL_Renderer* renderer, Difficulty& level);

void game(SDL_Window* window, SDL_Renderer* renderer, Difficulty& level);

#endif