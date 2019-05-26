
#include "virtual_machine.h"

void		free_args(t_area **p)
{
	if (*p)
	{
		free((*p)->map);
		free((*p)->players);
		free(*p);
	}
	*p = NULL;
}

