/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 07:43:12 by dwiegand          #+#    #+#             */
/*   Updated: 2018/12/03 04:08:18 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memcpy(void *dst, const void *src, size_t length)
{
	size_t		i;

	if (dst == src || length == 0)
		return (dst);
	i = -1;
	while (++i < length)
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
	return (dst);
}
