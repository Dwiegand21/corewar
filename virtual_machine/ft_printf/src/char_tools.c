/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 19:36:02 by dwiegand          #+#    #+#             */
/*   Updated: 2019/02/24 13:53:00 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

uint32_t	*wstrdup(uint32_t *str, uint32_t n)
{
	uint32_t	i;
	uint32_t	*array;

	i = 0;
	array = NULL;
	if (!(array = (uint32_t *)malloc(sizeof(uint32_t) * (n + 1))))
		return (NULL);
	while (i < n)
	{
		array[i] = str[i];
		i++;
	}
	array[i] = 0;
	return (array);
}

uint32_t	wstr_len(uint32_t *array)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	length;

	i = 0;
	length = 0;
	while (array[i])
	{
		j = 0;
		while (j < 4)
		{
			if ((array[i] >> (j * 8)) & 0xFF)
				length++;
			j++;
		}
		i++;
	}
	return (length);
}

void		wstr_cpy(char *str, uint32_t *array, uint32_t n)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (array[i])
	{
		j = 4;
		while (j > 0)
		{
			j--;
			if ((array[i] >> (j * 8)) & 0xFF)
				*str++ = (array[i] >> (j * 8)) & 0xFF;
			n--;
		}
		i++;
	}
	*str = 0;
}
