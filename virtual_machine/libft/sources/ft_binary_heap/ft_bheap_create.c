/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bheap_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 11:48:55 by dwiegand          #+#    #+#             */
/*   Updated: 2019/06/30 14:15:18 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_binary_heap_assets.h"

t_binary_heap		*ft_bheap_create(
										size_t n,
										int (*cmp)(void *, void *),
										void (*del)(void **))
{
	t_binary_heap	*p;

	p = NULL;
	if ((p = ft_memalloc(sizeof(t_binary_heap))) == NULL)
		ft_error(ERRALLOC, __func__);
	if ((p->data = ft_memalloc(sizeof(struct s_binary_heap_data))) == NULL)
		ft_error(ERRALLOC, __func__);
	BH_DATA(p)->vector = ft_vector_create(n, del);
	BH_DATA(p)->cmp = cmp;
	BH_DATA(p)->heap_size = 0;
	p->insert = &ft_bheap_insert;
	p->delete = &ft_bheap_delete_elem;
	p->get = &ft_bheap_get;
	p->extract = &ft_bheap_extract;
	p->size = &ft_bheap_size;
	p->get_vector = &ft_bheap_get_vector;
	return (p);
}
