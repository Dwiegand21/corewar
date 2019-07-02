
#ifndef LIBFT_FT_BINARY_HEAP_H
# define LIBFT_FT_BINARY_HEAP_H

# include <stdlib.h>
# include "ft_vector.h"

typedef struct s_binary_heap	t_binary_heap;

void			ft_bheap_insert(t_vector *v,
								void *elem,
								int (*cmp)(void*, void *));
void			*ft_bheap_get(t_vector *v);
void			*ft_bheap_extract(t_vector *v, int (*cmp)(void*, void *));
void			ft_bheap_delete_elem(t_vector *v, size_t index);
void			ft_bheap_init(t_vector *v, int (*cmp)(void *, void *));

#endif //LIBFT_FT_BINARY_HEAP_H
