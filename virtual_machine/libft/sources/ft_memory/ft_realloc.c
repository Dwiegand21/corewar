/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 20:12:47 by dwiegand          #+#    #+#             */
/*   Updated: 2019/07/04 16:56:05 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_memory.h"

void		*ft_realloc(void *mem, size_t old_size, size_t new_size)
{
	size_t	i;
	void	*new;

	new = NULL;
	new = ft_memalloc(new_size);
	if (new == NULL)
	{
		free(mem);
		return (NULL);
	}
	i = 0;
	while (i < old_size)
	{
		((char *)new)[i] = ((char *)mem)[i];
		i++;
	}
	free(mem);
	return (new);
}
