/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 07:45:37 by dwiegand          #+#    #+#             */
/*   Updated: 2018/11/22 07:45:39 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strncat(char *dst, const char *src, size_t n)
{
	char	*head;

	head = dst;
	if (n > 0)
	{
		while (*dst != 0)
			dst++;
		while (*src && n--)
		{
			*dst = *src;
			dst++;
			src++;
		}
		*dst = 0;
	}
	return (head);
}
