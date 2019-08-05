#ifndef VISUALIZATION_M_TYPES_H
# define VISUALIZATION_M_TYPES_H

#include <SDL_render.h>

typedef struct s_visualization		t_visualization;
typedef	struct s_texture			t_texture;
typedef struct s_font				t_font;

typedef struct s_button				t_button;

typedef enum
{
	BLACK,
	SILVER,
	RED,
	RED_INDIAN,
	RED_DARK,
	RED_VIOLET,
	GREEN,
	GREEN_YELLOW,
	GREEN_SPRING,
	GREEN_DARK,
	BLUE,
	BLUE_DEEP_SKY,
	BLUE_AQUAMARINE,
	BLUE_MEDIUM,
	BLUE_DARK,
	WHITE
}	t_colors;

struct		s_visualization
{
	SDL_Window		*window;
	SDL_Rect		window_rect;
	SDL_Surface		*screen;

	SDL_Renderer	*renderer;

	// Old
	SDL_Surface		*background;
};

struct		s_texture
{
	SDL_Texture		*texture;
	SDL_Rect		text_rect;
};

struct 		s_font
{
	const char 		ttf_file_name[70];
	int32_t			point_size;
};

struct		s_button
{
	t_texture		font;
	t_texture		button;

	int32_t			out_value;
};

#endif //VISUALIZATION_M_TYPES_H
