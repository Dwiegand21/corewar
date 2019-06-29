
#ifndef LIBFT_FT_BINARY_HEAP_ASSETS_H
# define LIBFT_FT_BINARY_HEAP_ASSETS_H

# include "ft_binary_heap.h"

struct		s_binary_heap_data
{
	size_t		heap_size;
	t_vector	*vector;
	int			(*cmp)(void *, void *);
};

# define BH_DATA(x)		((struct s_binary_heap_data *)((x)->data))

void			ft_bheap_insert()

#endif //LIBFT_FT_BINARY_HEAP_ASSETS_H
