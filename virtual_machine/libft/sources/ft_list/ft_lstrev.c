/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 18:39:14 by dwiegand          #+#    #+#             */
/*   Updated: 2018/11/29 20:32:43 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_list			*ft_lstrev(t_list **alst)
{
	t_list		*prev;
	t_list		*cur;
	t_list		*lost;

	if (!(*alst))
		return (*alst);
	prev = *alst;
	cur = prev->next;
	prev->next = NULL;
	while (cur)
	{
		lost = cur->next;
		cur->next = prev;
		prev = cur;
		cur = lost;
	}
	return (prev);
}
