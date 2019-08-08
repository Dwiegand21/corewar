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

	if (!(new = (t_process *)ft_memalloc(sizeof(t_process))))
		ft_error(ERRALLOC, __func__);
	new->player = (int32_t)player;
	new->reg[0] = ~player;
	new->pc = pc;
	set_process_sleep(new, MAP[new->pc]);
//	new->sleep = SN_CYCLES + 1;
//	new->f = g_ops[0].f;
	//new->sleep = SN_CYCLES + set_process_sleep(new, MAP[new->pc]);
	new->ordinal_number = area->g_stats.next_process_index++;
	new->next = NULL;
	new->n_lives = 0;
	//ft_bheap_insert(area->processes, new, &heap_cmp);
	//area->init_processes[SN_PROCESS++] = new;
	SN_PROCESS++;
	insert(&area->time[(area->current_index + new->sleep) % TIMELINE_SIZE], new);
}

static inline void ft_lst_push(t_process **lst, t_process *new)
{
	t_process *iter;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	iter = *lst;
	while (iter->next)
	{
		iter = iter->next;
	}
	iter->next = new;
}

t_process *extract_dead_node(t_process **dead)
{
	t_process *current;

	current = *dead;
	*dead = (*dead)->next;
	return (current);
}

void		new_process(t_area *area, t_process *process, uint32_t pc)
{
	t_process	*new;

	new = NULL;
	if (area->time[1001] != NULL)
		new = extract_dead_node(&area->time[TIMELINE_SIZE]);
	else if (!(new = (t_process *)ft_memalloc(sizeof(t_process))))
		ft_error(ERRALLOC, __func__);
	*new = *process;
	for (int i = 0; i < 16; i++)
	{
		new->reg[i] = process->reg[i];
	}
	new->pc = SHIFT(pc);
	set_process_sleep(new, MAP[new->pc]);
	new->next = NULL;
	new->n_lives = process->n_lives;
//	new->sleep = SN_CYCLES + 1;
//	new->f = g_ops[0].f;
	//new->sleep = SN_CYCLES + set_process_sleep(new, MAP[new->pc]);
	if (area->flags & STEP_DEBUG && SN_CYCLES >= g_db_from)
	{
		printf(">> new_process:\n>> op_name: %s (%.2hhx)\n>> process pc: %d\n>> run_round: %d\n",
				g_ops[((MAP[new->pc] > 0 && MAP[new->pc] < 17) ? MAP[new->pc] : 0)].name,
				MAP[new->pc],
				new->pc,
				new->sleep);
	}
	new->ordinal_number = area->g_stats.next_process_index++;
	insert(&area->time[(area->current_index + new->sleep) % TIMELINE_SIZE], new);
	//ft_bheap_insert(area->processes, new, &heap_cmp);
	SN_PROCESS++;
}

//int32_t			delete_not_live_processes(t_area *area)
//{
//	size_t		index;
//	size_t		length;
//	t_vector	*v;
//
//	v = area->processes;
//	length = area->processes->size(area->processes);
//	index = 0;
//	while (index < length)
//	{
//		if (((t_process *)(v->v[index]))->live_in_session == false)
//		{
//			free(v->v[index]);
//			v->v[index] = NULL;
//			V_DATA(v)->end--;
//			length--;
//			ft_bheap_swap(v->v + index, v->v + length);
//			SN_PROCESS--;
//		}
//		else
//		{
//			((t_process *)(v->v[index]))->live_in_session = false;
//			index++;
//		}
//	}
//	ft_bheap_init(v, &heap_cmp);
//	return (1);
//}