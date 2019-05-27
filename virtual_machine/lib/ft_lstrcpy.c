/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 20:44:00 by dwiegand          #+#    #+#             */
/*   Updated: 2018/11/30 21:07:09 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
				ft_lstdel(&copy, ft_memzerdel);
				return (copy);
			}
			lst = lst->next;
		}
	}
	return (copy);
}
