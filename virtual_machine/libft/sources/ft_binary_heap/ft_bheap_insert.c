/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bheap_insert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 12:11:52 by dwiegand          #+#    #+#             */
/*   Updated: 2019/06/30 13:04:51 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_binary_heap_assets.h"

void			ft_bheap_insert(t_binary_heap *this, void *elem)
{
	size_t		i;

	i = BH_DATA(this)->heap_size;
	BH_DATA(this)->heap_size++;
	BH_DATA(this)->vector->push_back(BH_DATA(this)->vector, elem);
	while (i != 0 && (BH_DATA(this)->cmp(BH_DATA(this)->vector->v[i],
			BH_DATA(this)->vector->v[PARENT(i)])) < 0)
	{
		ft_bheap_swap(&BH_DATA(this)->vector->v[i],
				&BH_DATA(this)->vector->v[PARENT(i)]);
		i = PARENT(i);
	}
}
