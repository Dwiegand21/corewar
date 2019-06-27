/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 16:55:36 by dwiegand          #+#    #+#             */
/*   Updated: 2019/06/09 10:03:10 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

t_area		*initialization_area(void)
{
	t_area		*area;

	area = NULL;
	if (!(area = ft_memalloc(sizeof(t_area))))
		ft_error(ERRALLOC, __func__);
	area->map = NULL;
	if (!(area->map = ft_memalloc(sizeof(char) * MEM_SIZE)))
		ft_error(ERRALLOC, __func__);
	SDIE_CYCLE = CYCLE_TO_DIE;
	SNOT_CHANGED = 0;
	SDUMP_CYCLE = -1;
	area->win = -1;
	return (area);
}
