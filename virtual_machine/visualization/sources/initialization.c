
#include "visualization.h"

static int32_t
initialize_sdl(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		fprintf(stderr, "Can not initialize video: %s\n", SDL_GetError());
		return (0);
	}
	return (1);
}

static int32_t
initialize_image(void)
{
	int32_t image_flags;

	image_flags =
			IMG_INIT_JPG |
			IMG_INIT_PNG;

	if (((IMG_Init(image_flags)) & image_flags) != image_flags)
	{
		fprintf(stderr, "Can not initialize image: %s\n", SDL_GetError());
		return (0);
	}
	return (1);
}

static int32_t
load_fonts(void)
{
	int32_t		i;

	i = 0;
	while (i < N_FONT)
	{
		g_fonts[i] = TTF_OpenFont(
				g_font_files[i].ttf_file_name,
				g_font_files[i].point_size);
		if (g_fonts[i] == NULL)
		{
			fprintf(stderr, "Can not open font: %s\n", SDL_GetError());
			close_n_fonts(i);
			return (0);
		}
		i++;
	}
	return (1);
}

static int32_t
initialize_ttf(void)
{
	if (TTF_Init() == -1)
	{
		fprintf(stderr, "Can not initialize TTF: %s\n", SDL_GetError());
		return (0);
	}
	if (load_fonts() == 0)
	{
		TTF_Quit();
		return (0);
	}
	return (1);
}

int32_t
initialization(t_visualization *const restrict v)
{
	v->window = NULL;
	v->renderer = NULL;
	v->screen = NULL;
	if (initialize_sdl() == 0)
		return (0);
	if (initialize_ttf() == 0)
	{
		SDL_Quit();
		return (0);
	}
	if (create_window(v) == 0)
		return (destroy_all(v));
	if (create_renderer(v) == 0)
		return (destroy_all(v));
	return (1);
}