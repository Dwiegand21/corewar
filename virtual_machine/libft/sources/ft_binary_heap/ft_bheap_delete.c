/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bheap_delete.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 13:20:40 by dwiegand          #+#    #+#             */
/*   Updated: 2019/06/30 13:20:40 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_binary_heap_assets.h"

void			ft_bheap_delete(t_binary_heap **this)
{
	if (this == NULL)
		return ;
	if (*this == NULL)
		return ;
	ft_vector_delete(&BH_DATA(*this)->vector);
	free((*this)->data);
	free(*this);
	*this = NULL;
}