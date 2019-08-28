/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <axtazy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 07:17:28 by axtazy            #+#    #+#             */
/*   Updated: 2019/01/05 13:51:24 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putlst(t_list *lst)
{
	if (!lst)
		write(1, "list is null\n", 13);
	while (lst)
	{
		if (lst->content)
		{
			write(1, lst->content, lst->content_size);
		}
		else
			write(1, "(null)", 6);
		write(1, "\n", 1);
		lst = lst->next;
	}
}
