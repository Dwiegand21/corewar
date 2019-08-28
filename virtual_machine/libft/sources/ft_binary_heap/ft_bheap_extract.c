/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bheap_extract.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 13:04:56 by dwiegand          #+#    #+#             */
/*   Updated: 2019/07/02 21:01:50 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_binary_heap_assets.h"

void			*ft_bheap_extract(t_vector *v, int (*cmp)(void*, void *))
{
	void		*root;

	if (V_DATA(v)->end == 0)
		ft_error("Binary heap is empty\n", __func__);
	root = v->v[0];
	V_DATA(v)->end--;
	v->v[0] =
			v->v[V_DATA(v)->end];
	v->v[V_DATA(v)->end] = NULL;
	ft_bheap_sift_down(v, 0, cmp);
	return (root);
}
