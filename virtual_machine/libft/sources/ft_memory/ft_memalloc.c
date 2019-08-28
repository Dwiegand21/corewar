/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <axtazy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:34:48 by dwiegand          #+#    #+#             */
/*   Updated: 2019/03/17 19:10:38 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void		*ft_memalloc(size_t size)
{
	char	*str;

	str = NULL;
	if (size && (str = malloc(sizeof(char *) * size)))
	{
		while (size--)
			str[size] = 0;
	}
	return ((void *)str);
}
