/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 18:20:56 by dwiegand          #+#    #+#             */
/*   Updated: 2018/11/29 18:53:39 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_lstlen(t_list *lst)
{
	unsigned int	length;

	length = 0;
	if (lst != NULL)
	{
		while (lst)
		{
			length++;
			lst = lst->next;
		}
	}
	return (length);
}
