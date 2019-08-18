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
	t_vm_vector_int *const	timeline = area->time;
	int						i;

	i = -1;
	free(area->map);
	free(area->players);
	while (++i < TIMELINE_SIZE)
		free(timeline[i].data);
	free(area->carriages->data);
	free(area->carriages);
	free(g_sort_buffer->data);
	free(g_sort_buffer);
	free(area);
}
