/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:36:38 by dwiegand          #+#    #+#             */
/*   Updated: 2018/11/29 15:36:40 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnbr(int n)
{
	if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putchar((n % 10) + 48);
	}
	else if (n < 0)
	{
		ft_putchar('-');
		if (n < -9)
			ft_putnbr((n / 10) * (-1));
		ft_putchar((n % 10) * (-1) + 48);
	}
	else
		ft_putchar(n + 48);
}
