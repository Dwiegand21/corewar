

#include "visualization.h"

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

bool
init(t_visualization *v)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("Can't init video: %s\n", SDL_GetError());
		return false;
	}

	int flags = IMG_INIT_JPG;
	if ( !( IMG_Init( flags ) & flags ) ) {
		printf("Can't init image: %s\n", IMG_GetError());
		return false;
	}

	v->window = SDL_CreateWindow("Растяжка PNG",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
	if (v->window == NULL) {
		printf("Can't create window: %s\n", SDL_GetError());
		return false;
	}
	v->screen = SDL_GetWindowSurface(v->window);
	return true;
}

bool
load(t_visualization *v)
{
	v->background = IMG_Load(IMAGE_DIR"background.2.jpg");
	if (v->background == NULL) {
		printf("Can't load: %s\n", IMG_GetError());
		return false;
	}
	v->background = SDL_ConvertSurface( v->background,
										v->screen->format,
										0 );
	if (v->background == NULL) {
		printf("Can't convert: %s\n", SDL_GetError());
		return false;
	}
	return true;
}

void
quit(t_visualization *v)
{
	SDL_FreeSurface(v->background);

	SDL_FreeSurface(v->screen);
	SDL_DestroyWindow(v->window);

	SDL_Quit();
	IMG_Quit();
}

int
SDL_example(int argc, char** args)
{
	t_visualization v;
	SDL_Texture *t;

	if ((init(&v)) == false)
	{
		system("pause");
		quit(&v);
		return 1;
	}

	if ((load(&v)) == false)
	{
		system("pause");
		quit(&v);
		return 1;
	}

	SDL_Rect bg_rect;
	bg_rect.w = SCREEN_WIDTH;
	bg_rect.h = SCREEN_HEIGHT;
	bg_rect.x = 0;
	bg_rect.y = 0;

	SDL_BlitScaled(v.background, NULL, v.screen, &bg_rect);

	SDL_Event event;
	bool running = true;
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
					running = false;
			}
			if (event.type == SDL_QUIT)
				running = false;
		}
		SDL_UpdateWindowSurface(v.window);
	}
	quit(&v);
	return 0;
}
