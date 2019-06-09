/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:38:19 by dwiegand          #+#    #+#             */
/*   Updated: 2018/12/01 20:43:47 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char			*ft_strmap(char const *s, char (*f)(char))
{
	unsigned int	length;
	char			*copy;

	copy = NULL;
	if (s && f)
	{
		length = -1;
		while (s[++length])
			;
		if ((copy = malloc(sizeof(char) * (length + 1))))
		{
			copy[length] = 0;
			while (length--)
			{
				copy[length] = (char)f(s[length]);
			}
		}
	}
	return (copy);
}
