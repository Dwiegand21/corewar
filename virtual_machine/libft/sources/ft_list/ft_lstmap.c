/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:34:23 by dwiegand          #+#    #+#             */
/*   Updated: 2019/06/09 07:53:28 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "ft_iostream.h"
#include "ft_memory.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*copy;

	copy = NULL;
	if (!lst || !f)
		return (NULL);
	while (lst)
	{
		if (!(ft_lstadd_back(&copy, ft_lstcpy_elem(f(lst)))))
		{
			ft_lstdel(&copy, ft_memclear_n_del);
			return (copy);
		}
		lst = lst->next;
	}
	return (copy);
}
