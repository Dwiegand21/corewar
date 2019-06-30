/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bheap_delete_elem.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 13:19:57 by dwiegand          #+#    #+#             */
/*   Updated: 2019/06/30 13:32:08 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_binary_heap_assets.h"

void			ft_bheap_delete_elem(t_binary_heap *this, size_t index)
{
	if (index >= BH_DATA(this)->heap_size)
		ft_error("Invalide delete elem index\n", __func__);
	BH_DATA(this)->vector->delete_elem(BH_DATA(this)->vector, index);			// delete elem (!!!)
	BH_DATA(this)->heap_size--;
	BH_DATA(this)->vector->v[index] =
			BH_DATA(this)->vector->v[BH_DATA(this)->heap_size];
	BH_DATA(this)->vector->v[BH_DATA(this)->heap_size] = NULL;
	V_DATA(BH_DATA(this)->vector)->end--;
	ft_bheap_shift_down(this, 0);
}