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
	if (!(new = malloc(sizeof(t_area))))
		ft_error(ERR_ALLOC);
	new->map = NULL;
	if (!(new->map = ft_memalloc(sizeof(char) * MEM_SIZE)))
		ft_error(ERR_ALLOC);
	new->cycle_to_die = CYCLE_TO_DIE;
	new->cycle_step = 0;
	new->round = 0;
	new->lives_in_round = 0;
	new->dump_round = 0;
	new->n_players = 0;
	new->n_processes = 0;
	new->processes = NULL;
	new->players = NULL;
	return (new);
}
