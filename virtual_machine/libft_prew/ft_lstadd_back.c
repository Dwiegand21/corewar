/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:23:43 by dwiegand          #+#    #+#             */
/*   Updated: 2018/11/29 20:35:15 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list		*head;

	if (new == NULL)
		return (0);
	if ((*alst) == NULL)
		*alst = new;
	else
	{
		head = *alst;
		while (head->next)
			head = head->next;
		head->next = new;
	}
	return (1);
}
