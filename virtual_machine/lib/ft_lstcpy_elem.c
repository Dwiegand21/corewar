/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpy_elem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 20:36:06 by dwiegand          #+#    #+#             */
/*   Updated: 2018/11/29 20:36:08 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list			*ft_lstcpy_elem(t_list *list)
{
	t_list		*elem;

	elem = NULL;
	if (!(elem = ft_lstnew(list->content, list->content_size)))
		return (NULL);
	return (elem);
}
