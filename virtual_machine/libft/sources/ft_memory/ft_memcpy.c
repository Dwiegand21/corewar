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

#include <stdlib.h>
#include <unistd.h>

//void		*ft_memcpy(void *dst, const void *src, size_t length)
//{
//	size_t		i;
//
//	if (dst == src || length == 0)
//		return (dst);
//	i = -1;
//	while (++i < length)
//		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
//	return (dst);
//}

void	*ft_memcpy(void *dest, const void *src, register size_t count)
{
	register ssize_t			*dst1;
	register const ssize_t	*src1;
	register char			*dst2;
	register const char		*src2;
	register size_t			n;

	if (dest == src)
		return (dest);
	dst1 = (ssize_t *)dest;
	src1 = (const ssize_t *)src;
	n = sizeof(ssize_t);
	while (count >= n)
	{
		*dst1++ = *src1++;
		count -= n;
	}
	dst2 = (char *)dst1;
	src2 = (const char *)src1;
	while (count--)
		*dst2++ = *src2++;
	return (dest);
}
