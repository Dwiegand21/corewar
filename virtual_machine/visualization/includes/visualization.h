
#ifndef VISUALIZATION_VISUALIZATION_H
# define VISUALIZATION_VISUALIZATION_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>

# if __has_include(<SDL2/SDL.h>)
#  include <SDL2/SDL.h>
#  include <SDL2/SDL_image.h>
#  include <SDL2/SDL_ttf.h>
#  include <SDL2/SDL_video.h>
# elif __has_include("SDL.h")
#  include "SDL.h"
#  include "SDL_image.h"
#  include "SDL_ttf.h"
#  include "SDL_video.h"
# elif __has_include("SDL2/SDL.h")
#  include "SDL2/SDL.h"
# endif

# include "m_types.h"
//# include <GL/gl.h>
//# include <GL/glu.h>

# define FONTS_PATH "../assets/fonts/"

# define N_FONT 3

extern const t_font g_font_files[N_FONT];
extern TTF_Font		*g_fonts[N_FONT];
extern SDL_Color	RGB_colors[];

int32_t
initialization(t_visualization *v);

int32_t
create_renderer(t_visualization *v);

int32_t
create_window(t_visualization *v);

SDL_Texture*
create_texture(SDL_Renderer *renderer, SDL_Surface *surf);

SDL_Cursor*
create_cursor(void);

int32_t
title_page(t_visualization *v);

int32_t
load_title_page(t_visualization *v);

void
close_n_fonts(int32_t n);

int32_t
destroy_all(t_visualization *v);


//  Old
int
SDL_example(int argc, char** argv);

#endif //VISUALIZATION_VISUALIZATION_H
