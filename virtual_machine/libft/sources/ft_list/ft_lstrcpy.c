/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 20:44:00 by dwiegand          #+#    #+#             */
/*   Updated: 2019/06/09 07:55:20 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "ft_list.h"

t_list			*ft_lstrcpy(t_list *lst)
{
	t_list		*copy;
	t_list		*elem;

	copy = NULL;
	if (lst)
	{
		while (lst)
		{
			if ((elem = ft_lstcpy_elem(lst)))
				ft_lstadd(&copy, elem);
			else
			{
				ft_lstdel(&copy, ft_memclear_n_del);
				return (copy);
			}
			lst = lst->next;
		}
	}
	return (copy);
}
