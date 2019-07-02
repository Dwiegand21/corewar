
#ifndef LIBFT_FT_BINARY_HEAP_ASSETS_H
# define LIBFT_FT_BINARY_HEAP_ASSETS_H

# include "ft_binary_heap.h"
# include "../ft_vector/ft_vector_assets.h"
# include "ft_project_assets.h"
# include "ft_memory.h"

# define PARENT(x)		((x - 1) / 2)
# define LEFT(x)		(x * 2 + 1)
# define RIGHT(x)		(x * 2 + 2)

struct		s_binary_heap_data
{
	size_t		heap_size;
	t_vector	*vector;
	int			(*cmp)(void *, void *);
};

# define BH_DATA(x)		((struct s_binary_heap_data *)((x)->data))

void			ft_bheap_swap(void **p1, void **p2);
void			ft_bheap_sift_down(t_vector *v,
									size_t index,
									int (*cmp)(void*, void *));

#endif //LIBFT_FT_BINARY_HEAP_ASSETS_H
