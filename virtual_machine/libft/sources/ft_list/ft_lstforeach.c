/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstforeach.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:57:39 by dwiegand          #+#    #+#             */
/*   Updated: 2018/11/29 20:23:36 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void			ft_lstforeach(t_list *lst, void (*f)(void *, size_t))
{
	if (lst && f)
		while (lst)
		{
			f(lst->content, lst->content_size);
			lst = lst->next;
		}
}
