#include "levels.h"
#include "window.h"
#include <windows.h>
#include <stdio.h>
#include <locale.h>

int main(int argc, char** argv)
{
    SetConsoleCP(65001);
	SetConsoleOutputCP(65001);

	InitSDL();
	
	bool quit = false;
	Difficulty level;
	AboutGame aboutGame;

	while (!quit)
	{
		quit = menu(window, ren, level, aboutGame);
		if (!quit)
			game(window, ren, level, aboutGame);
	}

    SDL_Delay(500);

	DeInitSDL(0);
	return 0;
}
