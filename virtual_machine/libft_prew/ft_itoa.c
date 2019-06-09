/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:10:14 by dwiegand          #+#    #+#             */
/*   Updated: 2018/12/03 14:39:32 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void			ft_set(char *array, int nbr, unsigned int i)
{
	if (nbr > 9)
	{
		ft_set(array, nbr / 10, i - 1);
		array[i] = (nbr % 10) + 48;
	}
	else if (nbr < 0)
	{
		*array = '-';
		if (nbr < -9)
			ft_set(array, (nbr / 10) * (-1), i - 1);
		array[i] = (nbr % 10) * (-1) + 48;
	}
	else
		array[i] = (nbr % 10) + 48;
}

static size_t		ft_nbrlen(int nbr)
{
	if (nbr > 9)
		return (1 + ft_nbrlen(nbr / 10));
	if (nbr < 0)
	{
		if (nbr < -9)
			return (2 + ft_nbrlen((nbr / 10) * (-1)));
		else
			return (2);
	}
	return (1);
}

char				*ft_itoa(int n)
{
	char		*array;
	size_t		length;

	array = NULL;
	length = ft_nbrlen(n);
	if (length != (size_t)-1 && (array = malloc(sizeof(char) * (length + 1))))
	{
		ft_set(array, n, length - 1);
		array[length] = 0;
	}
	return (array);
}
