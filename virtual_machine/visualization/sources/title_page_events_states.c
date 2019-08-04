
#include "visualization.h"

static int32_t
filter(void *user_data, SDL_Event *event)
{
	if (event->type == SDL_MOUSEMOTION)
	{
		if (!(event->motion.x > 190 && event->motion.y > 100 &&
			  event->motion.x < 890 && event->motion.y < 610))
			return (0);
	}
	if (event->type == SDL_MOUSEBUTTONDOWN)
	{
		if ((event->button.button & SDL_BUTTON_LEFT) == 0)
			return (0);
	}
	return (1);
}

int32_t
title_page_event_states(void)
{
	SDL_EventState(SDL_MOUSEWHEEL, 0);
	SDL_EventState(SDL_BUTTON_RIGHT, 0);
	SDL_EventFilter filter1 = filter;
	SDL_SetEventFilter(filter1, NULL);

	return (0);
}