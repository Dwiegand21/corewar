
#include "visualization.h"



int32_t
title_page(t_visualization *v)
{
	SDL_Event	event;
	bool		running = true;

	title_page_event_states();
	load_title_page(v);

	while (running)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_MOUSEMOTION)
		{
			printf("MMotion %d %d\n", event.motion.x, event.motion.y);
		}
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
				running = false;
			else
				printf("KDown %d\n", event.key.keysym.sym);
		}
		else if (event.type == SDL_KEYUP)
		{
			printf("KUp %d\n", event.key.keysym.sym);
		}
		else if (event.type == SDL_MOUSEWHEEL)
		{
			printf("MWheel %d %d\n", event.wheel.x, event.wheel.y);
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
				printf("BDown L %d %d\n", event.motion.x, event.motion.y);
			else if (event.button.button == SDL_BUTTON_RIGHT)
				printf("BDown R %d %d\n", event.motion.x, event.motion.y);
		}
		else if (event.type == SDL_WINDOWEVENT)
		{
			if (event.window.event == SDL_WINDOWEVENT_SHOWN)
				printf("window shown\n");
			else if (event.window.event == SDL_WINDOWEVENT_HIDDEN)
				printf("window_hidden\n");
			if (event.window.event == SDL_WINDOWEVENT_EXPOSED)
				printf("window exposed\n");
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				load_title_page(v);
		}
		else if (event.type == SDL_QUIT)
			running = false;

	}
	return (1);
}