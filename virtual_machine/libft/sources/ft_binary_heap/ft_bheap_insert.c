/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bheap_insert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 12:11:52 by dwiegand          #+#    #+#             */
/*   Updated: 2019/07/02 21:01:50 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_binary_heap_assets.h"

void			ft_bheap_insert(t_vector *v,
									void *const elem,
									int (*const cmp)(void*, void *))
{
	size_t		i;

	i = V_DATA(v)->end;
	v->push_back(v, elem);
	while (i != 0 && (*cmp)(v->v[i], v->v[PARENT(i)]) < 0)
	{
		ft_bheap_swap(v->v + i, v->v + PARENT(i));
		i = PARENT(i);
	}
}
