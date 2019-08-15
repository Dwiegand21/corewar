/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_processes_ops.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 16:11:21 by dwiegand          #+#    #+#             */
/*   Updated: 2019/07/03 17:59:45 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

#include "./../../libft/sources/ft_vector/ft_vector_assets.h"
#include "./../../libft/sources/ft_binary_heap/ft_binary_heap_assets.h"

void		load_process(t_area *area, int32_t player, uint32_t pc)
{
	t_process	*new;
	int i;

	if (!(new = (t_process *)ft_vm_vector_prc_push_back(&area->carriages)))
		ft_error(ERRALLOC, __func__);
	new->player = (int32_t)player;
	new->reg[0] = ~player;
	i = 0;
	while (++i < REG_NUMBER)
		new->reg[i] = 0;
	new->pc = pc;
	new->f = get_op;
	new->sleep = 1;

	///set_process_op_and_sleep(new, MAP[new->pc]);
//	new->sleep = SN_CYCLES + 1;
//	new->f = g_ops[0].f;
	//new->sleep = SN_CYCLES + set_process_op_and_sleep(new, MAP[new->pc]);
	new->ordinal_number = area->g_stats.next_process_index++;
	new->n_lives = 0;
	//ft_bheap_insert(area->processes, new, &heap_cmp);
	//area->init_processes[SN_PROCESS++] = new;
	SN_PROCESS++;
	ft_vm_vector_int_push_back((area->time + (area->current_index + new->sleep) % TIMELINE_SIZE),
							   new->ordinal_number);
	//insert(&area->time[(area->current_index + new->sleep) % TIMELINE_SIZE], new);
}

void		new_process(t_area *area, t_process *process, uint32_t pc) // todo maybe need to move backup here from forks
{
	t_process	*new;

	//if (area->time[TIMELINE_SIZE] != NULL)
	//	new = extract_dead_node(&area->time[TIMELINE_SIZE]);
	if (!(new = (t_process *)ft_vm_vector_prc_push_back(&area->carriages)))
		ft_error(ERRALLOC, __func__);
	*new = *process; // todo check if it copy whole structure
///	for (int i = 0; i < 16; i++)
///	{
///		new->reg[i] = process->reg[i];
///	}
	new->pc = SHIFT(pc);

	new->f = get_op;
	new->sleep = 1;

	///new->n_lives = process->n_lives;
	if (area->flags & STEP_DEBUG && SN_CYCLES >= g_db_from)
	{
		printf(">> new_process:\n>> op_name: %s (%.2hhx)\n>> process pc: %d\n>> run_round: %d\n",
				g_ops[((MAP[new->pc] > 0 && MAP[new->pc] < 17) ? MAP[new->pc] : 0)].name,
				MAP[new->pc],
				new->pc,
				new->sleep);
	}
	new->ordinal_number = area->g_stats.next_process_index++;
	ft_vm_vector_int_push_back((area->time + (area->current_index + new->sleep) % TIMELINE_SIZE),
							   new->ordinal_number);
	//insert(&area->time[(area->current_index + new->sleep) % TIMELINE_SIZE], new);
	SN_PROCESS++;
}
