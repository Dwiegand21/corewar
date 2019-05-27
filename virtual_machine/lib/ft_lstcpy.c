/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 20:40:31 by dwiegand          #+#    #+#             */
/*   Updated: 2018/12/03 14:35:49 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
				ft_lstdel(&copy, ft_memzerdel);
				return (copy);
			}
			lst = lst->next;
		}
	}
	return (copy);
}
