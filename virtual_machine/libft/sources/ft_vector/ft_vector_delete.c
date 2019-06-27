/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_delete.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 21:26:06 by dwiegand          #+#    #+#             */
/*   Updated: 2019/06/27 21:29:11 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include "ft_vector_func_name.h"

void		ft_vector_delete(t_vector **p)
{
	if (p == NULL)
		return ;
	if (*p == NULL)
		return ;
	free(V_DATA(*p)->begin);
	free((*p)->data);
	free(*p);
	*p = NULL;
}
