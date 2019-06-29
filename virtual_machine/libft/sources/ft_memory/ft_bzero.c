/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 07:40:43 by dwiegand          #+#    #+#             */
/*   Updated: 2018/12/29 16:48:59 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void		ft_bzero(void *dst, size_t length)
{
	long long int	*a;

	a = (long long *)dst;
	while (length >= sizeof(long long))
	{
		*a = 0L;
		a++;
		length -= sizeof(long long);
	}
	dst = (void *)a;
	while (length)
	{
		*(char *)dst = 0;
		dst++;
		length--;
	}
}
