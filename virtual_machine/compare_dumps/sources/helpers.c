/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 07:11:29 by axtazy            #+#    #+#             */
/*   Updated: 2019/06/07 12:49:27 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void		ft_error(const char *error)
{
	printf("%s\n", error);
	exit(1);
}


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
		if ((copy = (char *)malloc(sizeof(char) * (i + j + 1))))
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
