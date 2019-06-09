/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <axtazy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 07:45:07 by dwiegand          #+#    #+#             */
/*   Updated: 2019/01/05 06:37:00 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*d;
	size_t		res;

	d = dst;
	res = ft_strlen(src);
	while (*d != '\0' && size)
	{
		d++;
		size--;
	}
	res += (unsigned int)(d - dst);
	if (size != 0)
	{
		while (*src && size-- != 1)
			*d++ = *src++;
		*d = '\0';
	}
	return (res);
}
