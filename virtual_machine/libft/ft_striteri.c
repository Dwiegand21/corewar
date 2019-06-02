/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <axtazy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:37:50 by dwiegand          #+#    #+#             */
/*   Updated: 2019/01/05 06:36:29 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	char	*head;

	head = s;
	if (s && f)
	{
		while (*s)
		{
			f((unsigned int)(s - head), s);
			s++;
		}
	}
}
