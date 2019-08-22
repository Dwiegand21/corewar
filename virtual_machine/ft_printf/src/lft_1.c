/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lft_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 19:45:25 by dwiegand          #+#    #+#             */
/*   Updated: 2019/02/26 16:54:23 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strcat(char *dst, const char *src)
{
	int32_t		i;

	i = 0;
	while (dst[i] != '\0')
		i++;
	while ((dst[i] = *src) != '\0')
	{
		i++;
		src++;
	}
	return (dst);
}

char	*ft_strcpy(char *dst, const char *src)
{
	char		*copy;

	copy = dst;
	while ((*copy = *src) != '\0')
	{
		copy++;
		src++;
	}
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	char		*dup;
	int32_t		i;

	i = 0;
	while (s1[i] != '\0')
		i++;
	if (!(dup = (char *)malloc(sizeof(char) * (i + 1))))
		return ((char *)0);
	i = -1;
	while (s1[++i] != '\0')
		dup[i] = s1[i];
	dup[i] = '\0';
	return (dup);
}

char	*ft_strnew(size_t size)
{
	char		*mem;

	mem = NULL;
	if (size == (size_t)(-1))
		return ((void *)mem);
	if ((mem = (char *)malloc(size + 1)))
	{
		mem[size] = 0;
		while (size-- > 0)
			mem[size] = 0;
	}
	return ((void *)mem);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	while (n > 0)
	{
		n--;
		((char *)dst)[n] = ((char *)src)[n];
	}
	return (dst);
}
