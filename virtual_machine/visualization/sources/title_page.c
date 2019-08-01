
#include "visualization.h"

int32_t
filter(void *user_data, SDL_Event *event)
{
	if (event->type == SDL_MOUSEMOTION)
	{

	}
	if (event->type == SDL_MOUSEBUTTONDOWN)
	{
		if (event->button.button == SDL_BUTTON_LEFT)
			return (0);
	}
	return (1);
}

int32_t
setup_event_states()
{
	SDL_EventState(SDL_MOUSEWHEEL, 0);
	SDL_EventState(SDL_BUTTON_RIGHT, 0);
	SDL_EventFilter filter1 = filter;
	SDL_SetEventFilter(filter1, NULL);
}

int32_t
title_page(t_visualization *v)
{
	SDL_Event	event;
	bool		running = true;

	setup_event_states();
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
		}
		else if (event.type == SDL_QUIT)
			running = false;
	}
	return (1);
}