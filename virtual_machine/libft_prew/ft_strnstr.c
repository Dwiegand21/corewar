/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 07:46:33 by dwiegand          #+#    #+#             */
/*   Updated: 2018/12/01 20:43:47 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *hay, const char *needle, size_t length)
{
	const char	*go_needle;
	char		*head;

	if (*needle == 0)
		return ((char *)hay);
	while (*hay && length--)
	{
		go_needle = needle;
		if (*hay == *needle)
		{
			head = (char *)hay;
			while (*hay && *hay == *go_needle++)
			{
				if (*go_needle == 0 && (length >= (unsigned int)(hay - head)))
					return (head);
				hay++;
			}
			if (*hay == 0 || length <= (unsigned int)(hay - head))
				return (NULL);
			hay = head;
		}
		hay++;
	}
	return (NULL);
}
