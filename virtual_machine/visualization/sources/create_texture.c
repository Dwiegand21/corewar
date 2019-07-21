
#include "visualization.h"

SDL_Texture*
create_texture(
		SDL_Renderer *const restrict renderer,
		SDL_Surface *surf)
{
	SDL_Texture* texture;
	texture = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);
	return texture;
}