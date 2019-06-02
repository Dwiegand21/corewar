/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 07:47:03 by dwiegand          #+#    #+#             */
/*   Updated: 2019/03/07 22:52:03 by mwunsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strstr(const char *haystack, const char *needle)
{
	const char	*go_needle;
	const char	*head;

	if (*needle == 0)
		return ((char *)haystack);
	while (*haystack)
	{
		go_needle = needle;
		if (*haystack == *needle)
		{
			head = haystack;
			while (*haystack && *haystack++ == *go_needle++)
				if (*go_needle == 0)
					return ((char *)head);
			if (haystack == 0)
				return (NULL);
			haystack = head;
		}
		haystack++;
	}
	return (NULL);
}
