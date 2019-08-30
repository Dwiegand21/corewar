/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binary_heap.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 17:07:02 by dwiegand          #+#    #+#             */
/*   Updated: 2019/07/04 17:07:28 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_FT_BINARY_HEAP_H
# define LIBFT_FT_BINARY_HEAP_H

# include <stdlib.h>
# include "ft_vector.h"

void			ft_bheap_insert(t_vector *v,
								void *elem,
								int (*cmp)(void*, void *));
void			*ft_bheap_get(t_vector *v);
void			*ft_bheap_extract(t_vector *v, int (*cmp)(void*, void *));
void			ft_bheap_delete_elem(t_vector *v, size_t index);
void			ft_bheap_init(t_vector *v, int (*cmp)(void *, void *));
void			ft_bheap_sift_down(t_vector *v,
									size_t index,
									int (*cmp)(void*, void *));

#endif
