
#include "ft_vector_assets.h"

void		ft_vector_iter(const t_vector *const p, void (*f)(void **))
{
	size_t		i;
	size_t		length;

	if (p == NULL || f == NULL)
		return ;
	length = V_DATA(p)->end;
	i = 0;
	while (i < length)
	{
		f((V_DATA(p)->begin + i));
		i++;
	}
}