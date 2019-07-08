/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 20:40:31 by dwiegand          #+#    #+#             */
/*   Updated: 2019/06/09 07:55:20 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "ft_memory.h"

t_list		*ft_lstcpy(t_list *lst)
{
	t_list		*copy;

	copy = NULL;
	if (lst)
	{
		while (lst)
		{
			if (!(ft_lstadd_back(&copy, ft_lstcpy_elem(lst))))
			{
				ft_lstdel(&copy, ft_memclear_n_del);
				return (copy);
			}
			lst = lst->next;
		}
	}
	return (copy);
}
