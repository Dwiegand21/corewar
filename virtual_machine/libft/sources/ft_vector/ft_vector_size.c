
#include "ft_vector_assets.h"

size_t		ft_vector_size(const t_vector *const this)
{
	return (V_DATA(this)->end);
}