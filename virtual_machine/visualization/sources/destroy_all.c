
#include "visualization.h"

void
close_n_fonts(int32_t n)
{
	int32_t		i;

	i = 0;
	while (i < n)
	{
		TTF_CloseFont(g_fonts[i]);
		i++;
	}
}

int32_t
destroy_all(t_visualization *v)
{
	if (v->renderer != NULL)
		SDL_DestroyRenderer(v->renderer);
	if (v->screen != NULL)
		SDL_FreeSurface(v->screen);
	if (v->window != NULL)
		SDL_DestroyWindow(v->window);
	close_n_fonts(N_FONT);
	SDL_Quit();
	return (0);
}