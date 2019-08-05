
#include "visualization.h"

const struct s_font g_font_files[N_FONT] = {
		{"../assets/fonts/OpenSansCondensed-Light.ttf", 50},
		{"../assets/fonts/AmaticSC-Regular.ttf", 30},
		{"../assets/fonts/IndieFlower-Regular.ttf", 30}
};

TTF_Font *g_fonts[N_FONT] = { 0 };

SDL_Color RGB_colors[] = {
		{0, 0, 0, 0},				//	BLACK
		{152, 152, 152, 0},		//	SILVER
		{255, 0, 0, 0},			//	RED
		{205, 92, 92, 0},			//	RED_INDIAN
		{139, 0, 0, 0},			//	RED_DARK
		{199, 21, 133, 0},		//	RED_VIOLET
		{0, 255, 0, 0},			//	GREEN
		{173, 255, 47, 0},		//	GREEN_YELLOW
		{0, 255, 127, 0},			//	GREEN_SPRING
		{0, 100, 0, 0},			//	GREEN_DARK
		{0, 0, 255, 0},			//	BLUE
		{0, 191, 255, 0},			//	BLUE_DEEP_SKY
		{40, 255, 230, 0},		//	BLUE_AQUAMARINE
		{0, 0, 205, 0},			//	BLUE_MEDIUM
		{0, 0, 140, 0},			//	BLUE_DARK
		{255, 255, 255, 0}		//	WHITE
};
