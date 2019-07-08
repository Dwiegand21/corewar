/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:38:24 by dwiegand          #+#    #+#             */
/*   Updated: 2018/11/30 21:11:49 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char			*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*go;
	char			*copy;

	copy = NULL;
	if (s && f)
	{
		go = (char *)s;
		while (*go)
			go++;
		if ((copy = (char *)malloc(sizeof(char) * ((go - s) + 1))))
		{
			go = copy;
			while (*s)
			{
				*go = f((go - copy), *(char *)s);
				go++;
				s++;
			}
			*go = 0;
		}
	}
	return (copy);
}
