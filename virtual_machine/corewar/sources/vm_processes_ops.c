/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_processes_ops_NEW.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 16:11:21 by dwiegand          #+#    #+#             */
/*   Updated: 2019/06/30 16:32:56 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void		load_process(t_area *area, int32_t player, uint32_t pc)
{
	t_process	*new;

	new = NULL;
	if (!(new = (t_process *)ft_memalloc(sizeof(t_process))))
		ft_error(ERRALLOC, __func__);
	new->player = (int32_t)player;
	new->reg[0] = ~player;
	new->pc = pc;
	new->sleep = SN_CYCLES + get_process_sleep(new, MAP[new->pc]);
	area->processes_NEW->insert(area->processes_NEW, new);
	SN_PROCESS++;
}

void		new_process(t_area *area, t_process *process, uint32_t pc)
{
	t_process	*new;

	new = NULL;
	if (!(new = (t_process *)ft_memalloc(sizeof(t_process))))
		ft_error(ERRALLOC, __func__);
	*new = *process;
	new->pc = SHIFT(pc);
	new->sleep = SN_CYCLES + get_process_sleep(new, MAP[new->pc]);
	area->processes_NEW->insert(area->processes_NEW, new);
	SN_PROCESS++;
}

int32_t			delete_not_live_processes(t_area *area)
{
	size_t		index;
	t_vector	*v;

	v = area->processes_NEW->get_vector(area->processes_NEW);
	index = 0;
	while (v->v + index != v->end(v))
	{
		if (((t_process *)(v->v[index]))->live_in_session == false)
		{
			area->processes_NEW->delete_elem(area->processes_NEW, index);
			SN_PROCESS--;
		}
		else
			index++;
	}
	return (1);
}