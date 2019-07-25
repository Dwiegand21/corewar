
#include "visualization.h"

static void
init_window_rect(SDL_Rect *window_rect)
{
	window_rect->x = SDL_WINDOWPOS_CENTERED;
	window_rect->y = SDL_WINDOWPOS_CENTERED;
	window_rect->w = 1920;
	window_rect->h = 1080;
}

int32_t
create_window(t_visualization *const restrict v)
{
	int32_t window_flags;

	window_flags =
			SDL_WINDOW_SHOWN
			| SDL_WINDOW_RESIZABLE
//			| SDL_WINDOW_FULLSCREEN_DESKTOP
			;
	init_window_rect(&v->window_rect);
	v->window = SDL_CreateWindow(
			"Test",
			v->window_rect.x,
			v->window_rect.y,
			v->window_rect.w,
			v->window_rect.h,
			window_flags);
	if (v->window == NULL)
	{
		fprintf(stderr, "Can not create window: %s\n", SDL_GetError());
		return (0);
	}
	SDL_GetWindowSize(v->window, &v->window_rect.w, &v->window_rect.h);
	return (1);
}