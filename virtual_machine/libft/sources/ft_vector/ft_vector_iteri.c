/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_iteri.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 14:39:20 by dwiegand          #+#    #+#             */
/*   Updated: 2019/06/30 14:44:10 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector_assets.h"

void		ft_vector_iteri(const t_vector *const p,
							void (*f)(size_t index, void **elem))
{
	size_t		i;
	size_t		length;

	if (p == NULL || f == NULL)
		return ;
	length = V_DATA(p)->end - V_DATA(p)->begin;
	i = 0;
	while (i < length)
	{
		f(i, (V_DATA(p)->begin + i));
		i++;
	}
}

