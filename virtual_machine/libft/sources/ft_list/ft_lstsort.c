/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 13:50:02 by axtazy            #+#    #+#             */
/*   Updated: 2019/06/10 14:27:06 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_list			*ft_lstsort(t_list *const list, int (*f)(t_list *, t_list *))
{
	t_list	*a;
	t_list	*b;

	if (list == NULL || list->next == NULL)
		return (list);
	a = list;
	while (a != NULL)
	{
		b = a->next;
		while (b != NULL)
		{
			if ((f(a, b)) > 0)
				ft_lstswap(a, b);
			b = b->next;
		}
		a = a->next;
	}
	return (list);
}
