
#include "visualization.h"

int32_t
title_page(t_visualization *v)
{
	SDL_Event	event;
	bool		running = true;

	load_title_page(v);
	while (running)
	{
		SDL_WaitEvent(&event);
//		while (SDL_PollEvent(&event))
//		{
			if (event.type == SDL_QUIT)
				running = false;
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
					running = false;
			}
//		}
	}
	return (1);
}