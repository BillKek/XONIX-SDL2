#include "game.h"

int block_width = 20;
int point_per_block = 5;

void GameDraw(Game& game, Player& player)
{
	SDL_SetRenderDrawColor(ren, 0, 225, 225, 225);
	SDL_RenderClear(ren);

	SDL_Rect r = { player.x,player.y,17,17 };
	SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
	SDL_RenderDrawRect(ren, &r);
	SDL_RenderPresent(ren);
}

void GameUpdate(Game& game,Player& player)
{
	while (SDL_PollEvent(&game.ev))
	{
		switch (game.ev.type)
		{
		case SDL_QUIT:
			game.run = false;
			break;
		case SDL_KEYDOWN:
			switch (game.ev.key.keysym.scancode)
			{
			case SDL_SCANCODE_ESCAPE:	game.run = false;				break;
			case SDL_SCANCODE_UP:		game.moveStatus.up = true;		break;
			case SDL_SCANCODE_DOWN:		game.moveStatus.down = true;	break;
			case SDL_SCANCODE_RIGHT:	game.moveStatus.right= true;	break;
			case SDL_SCANCODE_LEFT:		game.moveStatus.left= true;		break;
			}
			break;
		case SDL_KEYUP:
			switch (game.ev.key.keysym.scancode)
			{
			case SDL_SCANCODE_UP:		game.moveStatus.up = false;		break;
			case SDL_SCANCODE_DOWN:		game.moveStatus.down = false;	break;
			case SDL_SCANCODE_RIGHT:	game.moveStatus.right = false;	break;
			case SDL_SCANCODE_LEFT:		game.moveStatus.left = false;	break;
			}
			break;
		}
		if (game.moveStatus.up && !game.moveStatus.down)		player.y -= 5;
		if (!game.moveStatus.up && game.moveStatus.down)		player.y += 5;
		if (game.moveStatus.right && !game.moveStatus.left)		player.x += 5;
		if (!game.moveStatus.right && game.moveStatus.left)		player.x -= 5;
	}
}

void GameLoop(Game& game, Player& player)
{
	while (game.run)
	{
		GameUpdate(game, player);
		GameDraw(game, player);
	}
}






/*void InitMap(Map& map)
{
	map.cols = (win_height - records_offset) / block_width;
	map.rows = win_width / block_width;
	for (int i = 0; i < map.rows; i++)
	{
		for (int j = 0; j < map.cols; j++)
		{
			map.blocks[i][j].x = i;
			map.blocks[i][j].y = j;
			if (i == 0 || j == 0 || i == map.rows - 1 || j == map.cols - 1)
				map.blocks[i][j].status.captured = true;
			else
				map.blocks[i][j].status.noncaptured = true;
		}
	}
}

void RenderMap(SDL_Renderer* ren, Map& map)
{
	SDL_Rect rect;
	rect.w = rect.h = block_width;
	for (int i = 0; i < map.rows; i++)
	{
		for (int j = 0; j < map.cols; j++)
		{
			rect.x = map.blocks[i][j].x * block_width;
			rect.y = map.blocks[i][j].y * block_width;

			if (map.blocks[i][j].status.captured == true)
				SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
			else if (map.blocks[i][j].status.noncaptured == true)
				SDL_SetRenderDrawColor(ren, 0, 100, 100, 255);
			else if (map.blocks[i][j].status.processed == true)
				SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
		}
		SDL_RenderFillRect(ren, &rect);
	}
}*/