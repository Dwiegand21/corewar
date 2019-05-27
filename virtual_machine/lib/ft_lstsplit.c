/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 14:03:12 by dwiegand          #+#    #+#             */
/*   Updated: 2018/12/01 20:51:53 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_memgo(const void **data, int c, size_t *length)
{
	while (*length && (**(unsigned char **)data) == c)
	{
		(*data)++;
		*length -= 1;
	}
	return (*length != 0);
}

static void		*ft_mset(const void **data, int c, size_t *length)
{
	void		*array;
	void		*head;

	array = NULL;
	head = NULL;
	if ((array = (void *)malloc(*length)))
	{
		head = array;
		while (*length && (**(unsigned char **)data) != c)
		{
			*(unsigned char *)array++ = **(unsigned char **)data;
			(*data)++;
			*length -= 1;
		}
	}
	return ((void *)head);
}

t_list			*ft_lstsplit(const void *data, int c, size_t length)
{
	t_list		*list;
	size_t		copy;

	list = NULL;
	if (data && length)
	{
		while (ft_memgo(&data, c, &length))
		{
			copy = length;
			if (!(ft_lstadd_back(&list,
				ft_lstnew(ft_mset(&data, c, &length), copy - length))))
			{
				ft_lstdel(&list, ft_memzerdel);
				return (list);
			}
		}
	}
	return (list);
}
