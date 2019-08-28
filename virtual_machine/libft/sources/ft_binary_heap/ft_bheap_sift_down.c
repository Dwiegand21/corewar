/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bheap_sift_down.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 17:38:59 by dwiegand          #+#    #+#             */
/*   Updated: 2019/07/04 17:38:59 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_binary_heap_assets.h"

void			ft_bheap_sift_down(t_vector *v,
									size_t index,
									int (*cmp)(void*, void *))
{
	size_t		left;
	size_t		right;
	size_t		min;
	size_t		length;

	length = V_DATA(v)->end;
	while (2 * index + 1 < length)
	{
		left = LEFT(index);
		right = RIGHT(index);
		min = left;
		if (right < length
			&& (*cmp)(v->v[right], v->v[left]) < 0)
			min = right;
		if ((*cmp)(v->v[index],
				v->v[min]) < 0)
			break ;
		ft_bheap_swap(v->v + index, v->v + min);
		index = min;
	}
}
