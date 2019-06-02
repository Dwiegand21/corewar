/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 07:46:14 by dwiegand          #+#    #+#             */
/*   Updated: 2018/12/01 20:43:47 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strncpy(char *dst, const char *src, size_t length)
{
	char	*head;

	head = dst;
	while (*src && length)
	{
		length--;
		*dst = *src;
		src++;
		dst++;
	}
	while (length--)
	{
		*dst = 0;
		dst++;
	}
	return (head);
}
