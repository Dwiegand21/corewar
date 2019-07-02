/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 14:56:45 by dwiegand          #+#    #+#             */
/*   Updated: 2019/06/30 14:56:45 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_vector_assets.h"

void		ft_vector_cat(t_vector *const this, const t_vector *const p)
{
	size_t		i;
	size_t		j;
	size_t		p_length;

	p_length = V_DATA(p)->end;
	j = V_DATA(this)->end;
	i = 0;
	while (i < p_length)
	{
		this->v[j] = p->v[i];
		j++;
		i++;
	}
}

void		ft_vector_destroy_tool(t_vector *p)
{
	free(p->data);
	free(p);
}