/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:34:23 by dwiegand          #+#    #+#             */
/*   Updated: 2018/12/03 14:36:05 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
			ft_lstdel(&copy, ft_memzerdel);
			return (copy);
		}
		lst = lst->next;
	}
	return (copy);
}
