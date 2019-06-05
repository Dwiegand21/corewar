/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 15:29:09 by axtazy            #+#    #+#             */
/*   Updated: 2019/06/05 17:40:58 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

static void			init_process_op(t_area *area, t_process *process)
{
	if (IS_REG(PPC(0)))
	{
		process->f = g_ops[PPC(0)].f;
		process->sleep = g_ops[PPC(0)].sleep - 1;
	}
	else
	{
		process->f = g_ops[0].f;
		process->sleep = g_ops[0].sleep - 1;
	}
	printf("[ %p ] pc: %u, f: %d\n", process, PC, ((IS_REG(PPC(0))) ? PPC(0) : 0));
}

static int32_t 		play_round(t_area *area)
{
	t_list		*cur;

	cur = area->processes;
	while (cur != NULL)
	{
		if (((t_process *)cur->content)->f == NULL)
			init_process_op(area, ((t_process *)cur->content));
		if (((t_process *)cur->content)->sleep == 0)
		{
			(((t_process *)cur->content)->f)(area, ((t_process *)cur->content));
			((t_process *)cur->content)->f = NULL;
		}
		else
			((t_process *)cur->content)->sleep--;
		cur = cur->next;
	}
	return (0);
}

int32_t				play_game(t_area *area)
{
	while (area->n_processes)
	{
		printf("round: %u\n", area->round);
		play_round(area);
		if (area->cycle_step >= area->cycle_to_die)
		{
			area->processes = delete_not_live_processes(area, area->processes);
			area->cycle_step = 0;
		}
		area->round++;
		area->cycle_step++;

	}
	return (0);
}