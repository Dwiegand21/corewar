
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
	void 		(*decrease)(t_binary_heap *this, int index, int new_key,
					void (*decrease_key)(void *));
	void 		(*delete)(t_binary_heap *this, int index);
};

t_binary_heap	*ft_bheap_create(size_t n, int (*cmp)(void *, void *),
					void (*del)(void **));
t_binary_heap	*ft_bheap_init(t_vector *v, int (*cmp)(void *, void *));
void			ft_bheap_delete(t_binary_heap **p);

#endif //LIBFT_FT_BINARY_HEAP_H
