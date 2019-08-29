/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_processes_ops.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 16:11:21 by dwiegand          #+#    #+#             */
/*   Updated: 2019/08/29 19:40:28 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

#include "../libft/sources/ft_vector/ft_vector_assets.h"
#include "../libft/sources/ft_binary_heap/ft_binary_heap_assets.h"

void		load_process(t_area *area, int32_t player, uint32_t pc)
{
	t_process	*new;
	int			i;

	if (!(new = (t_process *)ft_vm_vector_prc_push_back(&area->carriages)))
		ERRF(ERRALLOC);
	new->player = (int32_t)player;
	new->reg[0] = ~player;
	i = 0;
	while (++i < REG_NUMBER)
		new->reg[i] = 0;
	new->pc = pc;
	new->f = get_op;
	new->sleep = 1;
	new->ordinal_number = area->g_stats.next_process_index++;
	new->n_lives = 0;
	SN_PROCESS++;
	ft_vm_vector_int_push_back((area->time +
		(area->current_index + new->sleep) % TIMELINE_SIZE),
		new->ordinal_number);
}

void		new_process(t_area *area, t_process *process, uint32_t pc)
{
	t_process	*new;

	if (!(new = (t_process *)ft_vm_vector_prc_push_back(&area->carriages)))
		ERRF(ERRALLOC);
	*new = *process;
	for(int i = 0; i < REG_NUMBER; i++)
	{
		new->reg[i] = process->reg[i];
	}
	new->pc = SHIFT(pc);
	new->f = get_op;
	new->sleep = 1;
	new->ordinal_number = area->g_stats.next_process_index++;
	ft_vm_vector_int_push_back((area->time +
		(area->current_index + new->sleep) % TIMELINE_SIZE),
		new->ordinal_number);
	SN_PROCESS++;
}
