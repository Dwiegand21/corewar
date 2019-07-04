/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 13:56:56 by axtazy            #+#    #+#             */
/*   Updated: 2019/06/10 13:56:56 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void			ft_lstswap(t_list *a, t_list *b)
{
	t_list		c;

	c.content = a->content;
	c.content_size = a->content_size;
	a->content = b->content;
	a->content_size = b->content_size;
	b->content = c.content;
	b->content_size = c.content_size;
}
