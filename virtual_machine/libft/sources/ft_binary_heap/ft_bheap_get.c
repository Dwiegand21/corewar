/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bheap_get.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 12:14:23 by dwiegand          #+#    #+#             */
/*   Updated: 2019/06/30 12:14:23 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_binary_heap_assets.h"

void			*ft_bheap_get(t_vector *v)
{
	if (v->size(v) == 0)
		ft_error("Binary heap is empty\n", __func__);
	return (v->v[0]);
}