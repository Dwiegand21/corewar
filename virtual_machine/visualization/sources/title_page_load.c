
#include "visualization.h"

const char g_massege[3][10] = {
		"New",
		"Settings",
		"Exit"
};

static SDL_Texture*
load_font_textures(t_visualization *v)
{
	SDL_Color font_color = {0, 0, 0, 0};
	SDL_Surface *font = TTF_RenderText_Blended(
			g_fonts[0],
			"Hello",
			font_color);
	SDL_Texture *font_texture = create_texture(v->renderer, font);

	return (font_texture);
}

int32_t
f(t_visualization *v, t_texture *massage, SDL_Rect *button, const char *str)
{
	SDL_Color font_color = {225, 225, 225, 0};
	SDL_Surface *font = TTF_RenderText_Blended(
			g_fonts[0],
			str,
			font_color
			);
	massage->texture = create_texture(v->renderer, font);
	SDL_QueryTexture(
			massage->texture,
			NULL,
			NULL,
			&massage->text_rect.w,
			&massage->text_rect.h
			);
	massage->text_rect.x = (button->w - massage->text_rect.w) / 2 + button->x;
	massage->text_rect.y = (button->h - massage->text_rect.h) / 2 + button->y;
	return (0);
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
	SDL_RenderClear(v->renderer);
	SDL_SetRenderDrawColor(
			v->renderer,
			RGB_colors[RED_INDIAN].r,
			RGB_colors[RED_INDIAN].g,
			RGB_colors[RED_INDIAN].b,
			RGB_colors[RED_INDIAN].a
	);

	int32_t	width = 700,
			height = 500;
	SDL_Rect interface_bg_rect = {
			(v->window_rect.w - width) / 2,		//  .
			(v->window_rect.h - height) / 2,		//  .
			width,									//  .
			height };								//  .

	SDL_RenderFillRect(v->renderer, &interface_bg_rect);

	const int32_t n_buttons = 3;
	t_button button_list[3] = { 0 };
	SDL_Rect button_rect = {
			-1,
			-1,
			420,
			90
	};

	width = button_rect.w;
	height = (button_rect.h + 2) * n_buttons;


	SDL_Rect button_grid_rect = {
			(interface_bg_rect.w - width) / 2 + interface_bg_rect.x,		//  .
			(interface_bg_rect.h - height) / 2 + interface_bg_rect.y,	//  .
			width,															//  .
			height															//  .
	};

	button_rect.x = button_grid_rect.x;
	button_rect.y = button_grid_rect.y;

	SDL_SetRenderDrawColor(
			v->renderer,
			RGB_colors[WHITE].r,
			RGB_colors[WHITE].g,
			RGB_colors[WHITE].b,
			RGB_colors[WHITE].a
	);

	for (int i = 0; i < 3; i++)
	{
		SDL_RenderFillRect(v->renderer, &button_rect);
		f(v, &button_list[i].font, &button_rect, g_massege[i]);
		SDL_RenderCopy(v->renderer, button_list[i].font.texture, NULL, &button_list[i].font.text_rect);
		button_rect.y += button_rect.h + 2;
	}

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