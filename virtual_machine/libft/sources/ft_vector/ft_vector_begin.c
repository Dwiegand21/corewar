/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_begin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:32:59 by dwiegand          #+#    #+#             */
/*   Updated: 2019/06/27 20:08:28 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include "ft_vector_func_name.h"

void		*ft_vector_begin(const t_vector *restrict const this)
{
	return (*(((struct s_vector_data *)this->data)->begin));
}