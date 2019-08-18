/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 15:15:04 by axtazy            #+#    #+#             */
/*   Updated: 2019/06/10 03:31:09 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void		bytes_reverse(void *param, size_t size)
{
	size_t	i;
	char	tmp;

	i = 0;
	while (i < size / 2)
	{
		tmp = *(((char *)param) + i);
		*(((char *)param) + i) = *(((char *)param) + size - 1 - i);
		*(((char *)param) + size - 1 - i) = tmp;
		i++;
	}
}
