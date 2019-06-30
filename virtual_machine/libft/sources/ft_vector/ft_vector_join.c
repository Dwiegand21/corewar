/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:27:26 by dwiegand          #+#    #+#             */
/*   Updated: 2019/06/30 14:57:59 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector_assets.h"

t_vector		*ft_vector_join(const t_vector *const p1, const t_vector *const p2)
{
	size_t		new_size;
	t_vector	*new;

	new_size = (V_DATA(p1)->end - V_DATA(p1)->begin)
			   + (V_DATA(p2)->end - V_DATA(p2)->begin);
	if (new_size > V_DATA(p1)->size)
	{
		new_size = (size_t)((double)new_size * 1.4);
		new = ft_vector_create(new_size, V_DATA(p1)->free);
		ft_vector_cat(new, p1);
	}
	else
		new = (t_vector *)p1;
	ft_vector_cat(new, p2);
	return (new);
}
