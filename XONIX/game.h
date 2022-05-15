#include "window.h"

#pragma once

extern int block_width;
extern int point_per_block;

struct MoveStatus
{
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
};

struct Game
{
	bool run = true;
	SDL_Event ev;
};

struct Player
{
	/*SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Rect img_rect;
	SDL_Rect dst_rect;*/
	SDL_Rect rect = { win_width / 2,win_height / 2, 17 , 17 };
	MoveStatus moveStatus;
};

struct Enemies
{
	SDL_Rect rect = { win_width / 2 , win_height / 2, 17 , 17 };

	Uint32 lastTick;
	bool active = false;
	int minSpeed = 1;
	int maxSpeed = 4;
	int xSpeed = 2;
	int ySpeed = 2;
};

void InitPlayer(Player& player);

void InitEnemies(Enemies& enemies);

void GameDraw(Game& game, Player& player, Enemies& enemies);

void ProcessMove(Player& player, Enemies& enemies);

void ProcessMove2(Enemies& enemies);

void GameUpdate(Game& game, Player& player, Enemies& enemies);

void GameLoop(Game& game, Player& player, Enemies& enemies);


struct TypeBlock
{
	bool captured = true;
	bool processed = true;
	bool noncaptured = true;
};

struct Block
{
	int x;
	int y;
	TypeBlock status;
};

struct Map
{
	int cols;
	int rows;
	Block blocks[65][33];//32
};

void InitMap(Map& map);

void RenderMap(SDL_Renderer* ren, Map& map);