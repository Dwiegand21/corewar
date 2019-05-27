/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 07:43:42 by dwiegand          #+#    #+#             */
/*   Updated: 2018/12/01 20:43:47 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memset(void *dst, int value, size_t length)
{
	void	*head;

	head = dst;
	while (length)
	{
		(*(char *)dst++) = (char)value;
		length--;
	}
	return (head);
}
