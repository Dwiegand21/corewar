/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <axtazy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:09:01 by dwiegand          #+#    #+#             */
/*   Updated: 2019/03/30 18:30:32 by mwunsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnew(size_t size)
{
	unsigned	i;
	char		*str;

	i = 0;
	str = NULL;
	if ((str = (char *)malloc(sizeof(char) * (size + 1))))
	{
		while (i < size)
			str[i++] = 0;
		str[i] = 0;
	}
	return (str);
}
