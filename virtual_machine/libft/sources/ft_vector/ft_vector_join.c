/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:27:26 by dwiegand          #+#    #+#             */
/*   Updated: 2019/06/27 21:26:01 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include "ft_vector_assets.h"

static void		ft_vector_cat(t_vector *const this, const t_vector *const p)
{
	size_t		i;
	size_t		p_length;

	p_length = V_DATA(p)->end - V_DATA(p)->begin;
	i = 0;
	while (i < p_length)
	{
		*(V_DATA(this)->end) = p->v[i];
		V_DATA(this)->end++;
		i++;
	}
}

#include <stdio.h>

t_vector		*ft_vector_join(const t_vector *const p1, const t_vector *const p2)
{
	size_t		new_size;
	t_vector	*new;

	new_size = (V_DATA(p1)->end - V_DATA(p1)->begin)
			   + (V_DATA(p2)->end - V_DATA(p2)->begin);
	if (new_size > V_DATA(p1)->size)
	{
		printf("join: resize\n");
		new_size = (size_t)((double)new_size * 1.4);
		new = ft_vector_init(new_size, V_DATA(p1)->free);
		ft_vector_cat(new, p1);
	}
	else
		new = (t_vector *)p1;
	ft_vector_cat(new, p2);
	return (new);
}
