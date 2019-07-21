
#include "visualization.h"

static void
setup_renderer(t_visualization *const restrict v)
{
	SDL_RenderSetLogicalSize(
			v->renderer,
			v->window_rect.w,
			v->window_rect.h);
	SDL_SetRenderDrawColor(v->renderer,
			RGB_colors[BLACK].r,
			RGB_colors[BLACK].g,
			RGB_colors[BLACK].b,
			RGB_colors[BLACK].a);
}

int32_t
create_renderer(t_visualization *const restrict v)
{
	int32_t	renderer_flags;

	renderer_flags =
			SDL_RENDERER_ACCELERATED |
			SDL_RENDERER_TARGETTEXTURE;
	v->renderer = SDL_CreateRenderer(v->window, -1, renderer_flags);
	if (v->renderer == NULL)
	{
		fprintf(stderr, "Can not create renderer: %s\n", SDL_GetError());
		return (0);
	}
	setup_renderer(v);
	return (1);
}
