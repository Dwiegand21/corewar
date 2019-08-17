/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 16:55:36 by dwiegand          #+#    #+#             */
/*   Updated: 2019/05/27 16:55:36 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void		free_args(t_area *area)
{
	t_vm_vector_int * const	timeline = area->time;
	const int				count = TIMELINE_SIZE + 1;

	free(area->map);
	free(area->map_owners);
	free(area->players);
	for (int e = 0; e < count; ++e)
	{
		free(timeline[e].data);
	}
	free(area->carriages->data);
	free(area->carriages);
	free(buffer->data);
	free(buffer);
	free(area);
}
