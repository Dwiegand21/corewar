/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:37:56 by dwiegand          #+#    #+#             */
/*   Updated: 2019/03/24 17:00:16 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char		*copy;
	unsigned	i;
	unsigned	j;

	copy = NULL;
	if (s1 != NULL && s2 != NULL)
	{
		i = 0;
		j = 0;
		while (s1[i])
			i++;
		while (s2[j])
			j++;
		if ((copy = malloc(sizeof(char) * (i + j + 1))))
		{
			i = 0;
			while (*s1)
				copy[i++] = *s1++;
			while (*s2)
				copy[i++] = *s2++;
			copy[i] = 0;
		}
	}
	return (copy);
}
