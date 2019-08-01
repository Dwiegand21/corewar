
#include "visualization.h"

static SDL_Texture*
load_font_textures(t_visualization *v)
{
	SDL_Color font_color = {225, 225, 225, 0};
	SDL_Surface *font = TTF_RenderText_Blended(
			g_fonts[0],
			"Hello",
			font_color);
	SDL_Texture *font_texture = create_texture(v->renderer, font);

	return (font_texture);
}

int32_t
load_title_page_bg_texture(t_visualization *v)
{
	SDL_SetRenderDrawColor(
			v->renderer,
			RGB_colors[SILVER].r,
			RGB_colors[SILVER].g,
			RGB_colors[SILVER].b,
			RGB_colors[SILVER].a
			);

	SDL_RenderFillRect(v->renderer, NULL);
	SDL_SetRenderDrawColor(
			v->renderer,
			RGB_colors[RED_INDIAN].r,
			RGB_colors[RED_INDIAN].g,
			RGB_colors[RED_INDIAN].b,
			RGB_colors[RED_INDIAN].a
	);

	int32_t	width = 800,
			height = 600;
	SDL_Rect interface_bg_rect = {
			(v->window_rect.w - width) / 2, (v->window_rect.h - height) / 2,
			width, height
	};

	SDL_SetRenderDrawColor(
			v->renderer,
			RGB_colors[RED_INDIAN].r,
			RGB_colors[RED_INDIAN].g,
			RGB_colors[RED_INDIAN].b,
			RGB_colors[RED_INDIAN].a);

	SDL_RenderFillRect(v->renderer, &interface_bg_rect);
	SDL_RenderSetViewport(v->renderer, &interface_bg_rect);

	return (1);
}

int32_t
load_title_page(t_visualization *v)
{
	SDL_RenderClear(v->renderer);

	load_title_page_bg_texture(v);

	SDL_SetRenderDrawColor(
			v->renderer,
			RGB_colors[BLUE_DEEP_SKY].r,
			RGB_colors[BLUE_DEEP_SKY].g,
			RGB_colors[BLUE_DEEP_SKY].b,
			RGB_colors[BLUE_DEEP_SKY].a);
//	SDL_RenderSetViewport(v->renderer, NULL);

	SDL_RenderPresent(v->renderer);
	return (1);
}