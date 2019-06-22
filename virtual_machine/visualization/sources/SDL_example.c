
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "visualization.h"

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 700;

SDL_Window *win = NULL;
SDL_Surface *scr = NULL;
SDL_Surface *flower = NULL;

bool init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Can't init video: %s\n", SDL_GetError());
		return false;
	}

	int flags = IMG_INIT_JPG;
	if ( !( IMG_Init( flags ) & flags ) ) {
		printf("Can't init image: %s\n", IMG_GetError());
		return false;
	}

	win = SDL_CreateWindow(
			"Растяжка PNG",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
	if (win == NULL) {
		printf("Can't create window: %s\n", SDL_GetError());
		return false;
	}

	scr = SDL_GetWindowSurface(win);

	return true;
}

bool load() {
	flower = IMG_Load(IMAGE_DIR"background.2.jpg");
	if (flower == NULL) {
		printf("Can't load: %s\n", IMG_GetError());
		return false;
	}

	flower = SDL_ConvertSurface(flower, scr->format, 0);
	if (flower == NULL) {
		printf("Can't convert: %s\n", SDL_GetError());
		return false;
	}

	return true;
}

void quit() {
	SDL_FreeSurface(flower);

	SDL_FreeSurface(scr);
	SDL_DestroyWindow(win);

	SDL_Quit();
	IMG_Quit();
}

int
SDL_example(int argc, char** args)
{
	if (!init()) {
		system("pause");
		quit();
		return 1;
	}

	if (!load()) {
		system("pause");
		quit();
		return 1;
	}

	SDL_Rect bg_flower;
	bg_flower.w = SCREEN_WIDTH;
	bg_flower.h = SCREEN_HEIGHT;
	bg_flower.x = 0;
	bg_flower.y = 0;

	SDL_BlitScaled(flower, NULL, scr, &bg_flower);

	SDL_UpdateWindowSurface(win);

	//SDL_Delay(2000);
	while ()
	quit();

	return 0;
};
