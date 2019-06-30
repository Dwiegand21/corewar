/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bheap_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 12:39:22 by dwiegand          #+#    #+#             */
/*   Updated: 2019/06/30 13:27:56 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_binary_heap_assets.h"

void			ft_bheap_swap(void **p1, void **p2)
{
	void	*tmp;

	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void			ft_bheap_shift_down(t_binary_heap *this, size_t index)
{
	size_t		left;
	size_t		right;
	size_t		min;

	while (2 * index + 1 < BH_DATA(this)->heap_size)
	{
		left = LEFT(index);
		right = RIGHT(index);
		min = left;
		if (right < BH_DATA(this)->heap_size
			&& BH_DATA(this)->cmp(BH_DATA(this)->vector->v[right],
			BH_DATA(this)->vector->v[left]) < 0)
			min = right;
		if (BH_DATA(this)->cmp(BH_DATA(this)->vector->v[index],
			BH_DATA(this)->vector->v[min]) < 0)
			break ;
		ft_bheap_swap(&BH_DATA(this)->vector->v[index],
			&BH_DATA(this)->vector->v[min]);
		index = min;
	}
}