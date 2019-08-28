/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 16:55:36 by dwiegand          #+#    #+#             */
/*   Updated: 2019/05/27 16:55:36 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

t_area		*initialization_area(void)
{
	t_area		*new;

	new = NULL;
	if (!(new = ft_memalloc(sizeof(t_area))))
		ft_error(ERR_ALLOC);
	new->map = NULL;
	if (!(new->map = ft_memalloc(sizeof(char) * MEM_SIZE)))
		ft_error(ERR_ALLOC);
	new->cycle_to_die = CYCLE_TO_DIE;
	new->dump_round = -1;
	return (new);
}
