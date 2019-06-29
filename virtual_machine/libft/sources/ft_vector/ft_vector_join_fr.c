
#include "ft_vector_assets.h"

static void		ft_vector_destroy(t_vector *p)
{
	free(p->data);
	free(p);
}

t_vector		*ft_vector_join_fr(t_vector *p1, t_vector *p2)
{
	size_t		new_size;
	t_vector	*new;

	new_size = (V_DATA(p1)->end - V_DATA(p1)->begin)
			   + (V_DATA(p2)->end - V_DATA(p2)->begin);
	if (new_size > V_DATA(p1)->size)
	{
		printf("join: resize\n");
		new_size = (size_t)((double)new_size * 1.4);
		new = ft_vector_init(new_size, V_DATA(p1)->free);
		ft_vector_cat(new, p1);
		ft_vector_destroy(p1);
	}
	else
		new = p1;
	ft_vector_cat(new, p2);
	ft_vector_destroy(p2);
	return (new);
}