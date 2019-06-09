/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:34:38 by dwiegand          #+#    #+#             */
/*   Updated: 2018/12/03 14:36:08 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list		*elem;

	elem = NULL;
	if ((elem = (t_list *)malloc(sizeof(t_list))))
	{
		elem->content = NULL;
		elem->content_size = content_size;
		if (content && (elem->content = ft_memalloc(content_size)))
			ft_memcpy(elem->content, content, content_size);
		else
		{
			elem->content_size = 0;
			elem->content = NULL;
		}
		elem->next = NULL;
	}
	return (elem);
}
