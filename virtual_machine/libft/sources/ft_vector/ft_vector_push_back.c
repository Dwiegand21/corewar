/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_push_back.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:27:20 by dwiegand          #+#    #+#             */
/*   Updated: 2019/06/27 21:53:05 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include "ft_vector_func_name.h"
#include "ft_project_assets.h"
#include "ft_memory.h"

void		ft_vector_push_back(t_vector *this, void *elem)
{
	size_t		new_size;
	int			ptr_pos;
	int 		end_pos;

	if (V_DATA(this)->end == V_DATA(this)->begin + V_DATA(this)->size)
	{
		new_size = (size_t)((double)V_DATA(this)->size * 1.8);
		ptr_pos = this->v - V_DATA(this)->begin;
		end_pos = V_DATA(this) - V_DATA(this);
		V_DATA(this)->begin =
				ft_realloc(*V_DATA(this)->begin, V_DATA(this)->size, new_size);
		if (V_DATA(this)->begin == NULL)
			ft_error(ERRALLOC, __func__);
		V_DATA(this)->size = new_size;
		V_DATA(this)->end = V_DATA(this)->begin + end_pos;
		this->v = V_DATA(this)->begin + ptr_pos;
	}
	V_DATA(this)->end = elem;
	V_DATA(this)->end++;
}