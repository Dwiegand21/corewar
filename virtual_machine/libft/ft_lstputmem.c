/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstputmem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 18:26:26 by dwiegand          #+#    #+#             */
/*   Updated: 2018/12/01 19:31:51 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_lstputmem(t_list *lst)
{
	if (lst)
	{
		while (lst)
		{
			ft_putmem(lst->content, lst->content_size);
			write(1, "\n", 1);
			lst = lst->next;
		}
	}
}
