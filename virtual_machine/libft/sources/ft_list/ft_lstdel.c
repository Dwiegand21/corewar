/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:33:18 by dwiegand          #+#    #+#             */
/*   Updated: 2018/12/03 14:35:53 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include <stdlib.h>

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list		*go;

	go = NULL;
	if (*alst != NULL && del != NULL)
	{
		while (*alst)
		{
			go = (*alst)->next;
			del((*alst)->content, (*alst)->content_size);
			(*alst)->next = NULL;
			free(*alst);
			*alst = go;
		}
	}
}
