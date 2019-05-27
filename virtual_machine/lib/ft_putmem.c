/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putmem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 18:29:12 by dwiegand          #+#    #+#             */
/*   Updated: 2018/12/03 13:25:12 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_putmem(void *data, size_t length)
{
	int		i;

	if (!data)
	{
		write(1, "(null)", 7);
		return ;
	}
	write(1, "|", 1);
	while (length--)
	{
		i = 7;
		while (i > -1)
		{
			ft_putchar(((*(char *)data >> i) & 0x01) + 48);
			i--;
		}
		write(1, "|[ ", 3);
		ft_putnbr(*(unsigned char *)data);
		write(1, " ]; ", 4);
		if (length)
			write(1, "|", 1);
		data++;
	}
	write(1, "|", 1);
}
