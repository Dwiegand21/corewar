
#ifndef LIBFT_FT_BINARY_HEAP_ASSETS_H
# define LIBFT_FT_BINARY_HEAP_ASSETS_H

# include "ft_binary_heap.h"
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

void			ft_bheap_insert(t_binary_heap *this, void *elem);
void			*ft_bheap_get(t_binary_heap *this);
void			*ft_bheap_extract(t_binary_heap *this);
void			ft_bheap_delete_elem(t_binary_heap *this, size_t index);
size_t			ft_bheap_size(t_binary_heap *this);
t_vector		*ft_bheap_get_vector(t_binary_heap *this);

/*
**		ft_bheap_tools.c
*/
void			ft_bheap_swap(void **p1, void **p2);
void			ft_bheap_shift_down(t_binary_heap *this, size_t index);

#endif //LIBFT_FT_BINARY_HEAP_ASSETS_H
