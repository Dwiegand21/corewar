
#ifndef LIBFT_FT_BINARY_HEAP_H
# define LIBFT_FT_BINARY_HEAP_H

# include <stdlib.h>
# include "ft_vector.h"

typedef struct s_binary_heap	t_binary_heap;

struct s_binary_heap
{
	void 		*data;
	void 		(*insert)(t_binary_heap *this, void *);
	void 		*(*get)(t_binary_heap *this);
	void 		*(*extract)(t_binary_heap *this);
	void 		(*delete)(t_binary_heap *this, size_t index);
	size_t		(*size)(t_binary_heap *this);
	t_vector	*(*get_vector)(t_binary_heap *this);
};

t_binary_heap	*ft_bheap_create(size_t n, int (*cmp)(void *, void *),
					void (*del)(void **));
void			ft_bheap_delete(t_binary_heap **this);

#endif //LIBFT_FT_BINARY_HEAP_H
