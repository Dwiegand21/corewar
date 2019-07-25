#ifndef VISUALIZATION_M_TYPES_H
# define VISUALIZATION_M_TYPES_H

typedef struct s_visualization		t_visualization;
typedef	struct s_texture			t_texture;
typedef struct s_font				t_font;

typedef struct s_widget_list		t_widget_list;
typedef struct s_widget				t_widget;

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
}		t_colors;

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
	SDL_Rect		rect;
};

struct 		s_font
{
	const char 		ttf_file_name[70];
	int32_t			point_size;
};

struct		s_widget
{
	SDL_Rect		widget_rect;
	t_texture		widget_texture;

	int32_t			click_event_ret;
};

struct		s_widget_list
{
	t_widget		*widgets;
	int32_t			num_widgets;

	int				(*click_event_func)(t_widget *, void *);
};

#endif //VISUALIZATION_M_TYPES_H
