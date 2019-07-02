/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bheap_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:27:54 by dwiegand          #+#    #+#             */
/*   Updated: 2019/07/02 19:27:54 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_binary_heap_assets.h"

void		ft_bheap_init(t_vector *v, int (*cmp)(void *, void *))
{
	register size_t 	i;

	i = V_DATA(v)->size / 2;
	while (i > 0)
	{
		ft_bheap_sift_down(v, i, cmp);
		i--;
	}
}