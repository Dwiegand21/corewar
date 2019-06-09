/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:33:08 by dwiegand          #+#    #+#             */
/*   Updated: 2018/12/03 14:35:46 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstadd(t_list **alst, t_list *new)
{
	t_list	*go;

	if (new != NULL)
	{
		if ((*alst) == NULL)
			*alst = new;
		else
		{
			go = *alst;
			new->next = go;
			*alst = new;
		}
	}
}
