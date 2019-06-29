/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:41:54 by dwiegand          #+#    #+#             */
/*   Updated: 2018/11/29 21:55:16 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char		*ft_strtrim(char const *s)
{
	char			*array;
	unsigned int	i;

	array = NULL;
	if (s == NULL)
		return (array);
	while (*s && (*s == '\n' || *s == '\t' || *s == ' '))
		s++;
	i = 0;
	while (*(s + i))
		i++;
	while (i && (*(s + i - 1) == ' ' || *(s + i - 1) == '\t'
		|| *(s + i - 1) == '\n'))
		i--;
	if ((array = malloc(sizeof(char) * i + 1)))
	{
		array[i] = '\0';
		while (i--)
			array[i] = s[i];
	}
	return (array);
}
