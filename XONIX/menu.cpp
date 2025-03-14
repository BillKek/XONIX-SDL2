#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "menu.h"

void InitBackground(SDL_Renderer* ren, Background& background)
{
	char picture[] = "resources/background.jpeg";

	background.surfaceBack = IMG_Load(picture);
	if (background.surfaceBack == NULL)	printf("Не удалось загрузить картинку %s", picture);
	background.textureBack = SDL_CreateTextureFromSurface(ren, background.surfaceBack);
	SDL_FreeSurface(background.surfaceBack);
}

void InitButtons(SDL_Renderer* ren, MenuButton& menuButton)
{
	char pictureButton[] = "resources/button.bmp";
	char nameButton[5][30] = { "Лёгкий уровень", "Средний уровень", "Тяжёлый уровень", "О игре", "Выйти" };
	char rec_file[] = "resources/records.txt";

	FILE* file;
	SDL_Color colorRec = { 0, 0, 0 , 255 };
	fopen_s(&file, rec_file, "r");
	if (file == NULL)		printf("Не удалось открыть файл %s", rec_file);

	for (int number = 0; number < BUTTON_COUNT; number++)
	{
		InitFont(menuButton.button[0].font);
		SDL_Color color = { 0, 0, 0 , 255 };
		menuButton.button[number].textButton = TTF_RenderUTF8_Blended(menuButton.button[0].font, nameButton[number], color);

		menuButton.button[number].button.x = WIN_WIDTH / 2 - BUTTON_WIDTH / 4 * 3;
		menuButton.button[number].button.y = WIN_HEIGHT / 6 + number * 100;
		menuButton.button[number].button.w = BUTTON_WIDTH;
		menuButton.button[number].button.h = BUTTON_HEIGHT;

		SDL_Surface* surface = IMG_Load(pictureButton);
		if (surface == NULL)	printf("Не удалось загрузить картинку %s", pictureButton);
		menuButton.button[number].buttonBack = SDL_CreateTextureFromSurface(ren, surface);
		SDL_FreeSurface(surface);

		if (number != BUTTON_COUNT - 2)
		{
			char* textRec = (char*)calloc(20, sizeof(char));
			strcat_s(textRec, 20, "Рекорд: ");
			char* tmp = (char*)calloc(6, sizeof(char)); // 5 + нуль терминатор
			long records;
			fscanf_s(file, "%d", &records, 20);
			_itoa_s(records, tmp, 6, 10);
            //sprintf_s(tmp,6,"%d",records);
            //printf(tmp);
            //printf("\n---\n");

			strcat_s(textRec, 20, tmp);

			menuButton.button[number].textRec = TTF_RenderUTF8_Blended(menuButton.button->font, textRec, colorRec);

			free(textRec);
			free(tmp);
		}
	}
	fclose(file);
}

void RenderBackground(SDL_Renderer* ren, Background& background)
{
	SDL_RenderCopy(ren, background.textureBack, NULL, NULL);
}

void RenderButtons(SDL_Renderer* ren, MenuButton& menuButton)
{
	for (int number = 0; number < BUTTON_COUNT; number++)
	{
		SDL_RenderCopy(ren, menuButton.button[number].buttonBack, NULL, &menuButton.button[number].button);
		
		SDL_Texture* tButton = SDL_CreateTextureFromSurface(ren, menuButton.button[number].textButton);
		SDL_Rect rButton = { (int)(WIN_WIDTH / 2 - BUTTON_WIDTH / 4 * 2.5), (int)(WIN_HEIGHT / 6 + 7 + number * 100), 300, 50 };
		SDL_RenderCopy(ren, tButton, NULL, &rButton);
		SDL_DestroyTexture(tButton);

		if (number != BUTTON_COUNT - 1 && number != BUTTON_COUNT - 2)
		{
			SDL_Texture* tRec = SDL_CreateTextureFromSurface(ren, menuButton.button[number].textRec);
			SDL_Rect rRec = { menuButton.button[number].button.x + menuButton.button[number].button.w + 25, menuButton.button[number].button.y + 10, 200, 50 };
			SDL_RenderCopy(ren, tRec, NULL, &rRec);
			SDL_DestroyTexture(tRec);
		}
	}
}

void RenderMenu(SDL_Renderer* ren, Background& background, MenuButton& menuButton)
{
	RenderBackground(ren, background);
	RenderButtons(ren, menuButton);
}

int UpdateMenu(SDL_Event* event, MenuButton& menuButton)
{
	if (event->type == SDL_MOUSEBUTTONDOWN)
		for (int number = 0; number < BUTTON_COUNT; number++)
		{
			if (((menuButton.button[number].button.x <= event->button.x) && (event->button.x <= menuButton.button[number].button.x + menuButton.button[number].button.w))
				&& ((menuButton.button[number].button.y <= event->button.y) && (event->button.y <= menuButton.button[number].button.y + menuButton.button[number].button.h)))
			{
				if (number + 1 == 5)
					return 0;
				else
					return number + 1;
			}
		}

return -1;
}

void DestructMenu(Background& background, MenuButton& menuButton)
{
	SDL_DestroyTexture(background.textureBack);
	TTF_CloseFont(menuButton.button->font);
	TTF_Quit();
	for (int number = 0; number < BUTTON_COUNT; number++)
	{
		SDL_DestroyTexture(menuButton.button[number].buttonBack);
		SDL_FreeSurface(menuButton.button[number].textButton);

		if (number != BUTTON_COUNT - 1 && number != BUTTON_COUNT - 2)
			SDL_FreeSurface(menuButton.button[number].textRec);
	}
}