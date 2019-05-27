/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:41:48 by dwiegand          #+#    #+#             */
/*   Updated: 2018/11/29 15:41:49 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char		*copy;
	char		*go;

	copy = NULL;
	if (s != NULL)
	{
		if ((copy = malloc(sizeof(char) * (len + 1))))
		{
			go = copy;
			while (len-- && s[start])
			{
				*go = s[start++];
				go++;
			}
			*go = '\0';
		}
	}
	return (copy);
}
