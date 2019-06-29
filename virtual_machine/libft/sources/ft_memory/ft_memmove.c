/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 07:43:27 by dwiegand          #+#    #+#             */
/*   Updated: 2018/12/03 02:51:28 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void		*ft_memmove(void *dst, const void *src, size_t length)
{
	char	*head;

	head = dst;
	if (dst == src || length == 0)
		return (dst);
	if (dst > src)
	{
		dst += length;
		src += length;
		while (length--)
			*(unsigned char *)--dst = *(unsigned char *)--src;
	}
	else
	{
		while (length--)
			*(unsigned char *)dst++ = *(unsigned char *)src++;
	}
	return (head);
}
