/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <axtazy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 07:42:56 by dwiegand          #+#    #+#             */
/*   Updated: 2019/01/05 06:39:52 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void		*ft_memccpy(void *dst, const void *src, int c, size_t length)
{
	while (length--)
		if ((*(char *)dst++ = *(char *)src++) == (char)c)
			return (dst);
	return (NULL);
}
