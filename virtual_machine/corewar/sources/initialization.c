/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 16:55:36 by dwiegand          #+#    #+#             */
/*   Updated: 2019/07/02 22:37:35 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

t_area		*initialization_area(void)
{
	t_area		*area;

	if (!(area = ft_memalloc(sizeof(t_area))))
		ft_error(ERRALLOC, __func__);
	if (!(area->map = ft_memalloc(sizeof(char) * MEM_SIZE)))
		ft_error(ERRALLOC, __func__);
	if (!(area->map_owners = ft_memalloc(sizeof(char) * MEM_SIZE)))
		ft_error(ERRALLOC, __func__);

	for (int e = 0; e < MEM_SIZE; ++e)
		area->map_owners[e] = -1;

	if (!(area->carriages = ft_make_vm_vector_prc(INIT_CARRIAGES_COUNT)))
		ft_error(ERRALLOC, __func__);

	SDIE_CYCLE_DELTA = CYCLE_TO_DIE;
	SDIE_CYCLE = SDIE_CYCLE_DELTA;
	SNOT_CHANGED = 0;
	SN_CYCLES = 0;
	SDUMP_CYCLE = -1;
	area->win = -1;
	area->g_stats.next_process_index = 0;
	return (area);
}
