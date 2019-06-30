/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bheap_extract.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 13:04:56 by dwiegand          #+#    #+#             */
/*   Updated: 2019/06/30 13:04:56 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_binary_heap_assets.h"

void			*ft_bheap_extract(t_binary_heap *this)
{
	void		*root;

	if (BH_DATA(this)->heap_size == 0)
		ft_error("Binary heap is empty\n", __func__);
	root = BH_DATA(this)->vector->v[0];
	BH_DATA(this)->heap_size--;
	BH_DATA(this)->vector->v[0] =
			BH_DATA(this)->vector->v[BH_DATA(this)->heap_size];
	BH_DATA(this)->vector->v[BH_DATA(this)->heap_size] = NULL;
	V_DATA(BH_DATA(this)->vector)->end--;
	ft_bheap_shift_down(this, 0);
	return (root);
}