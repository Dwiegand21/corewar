/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bheap_get_vector.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 14:13:35 by dwiegand          #+#    #+#             */
/*   Updated: 2019/06/30 14:13:35 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_binary_heap_assets.h"

t_vector		*ft_bheap_get_vector(t_binary_heap *this)
{
	return (BH_DATA(this)->vector);
}