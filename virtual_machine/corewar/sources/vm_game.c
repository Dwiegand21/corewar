/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 17:23:31 by dwiegand          #+#    #+#             */
/*   Updated: 2019/07/04 19:53:56 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

static void			winner(t_area *area)
{
	printf("Contestant %d, \"%s\", has won !\n",
			area->players[area->win].ordinal_number,
			area->players[area->win].name);
	fflush(stdout);
}

int32_t				get_process_sleep(t_process *process, u_char byte)
{
	if (byte > 0 && byte < 17)
	{
		process->f = g_ops[byte].f;
		return (g_ops[byte].sleep);
	}
	else
	{
		process->f = NULL;
		return (1);
	}
}

static int			func_index(void (*f)(t_area *, t_process *))
{
	for (int i = 0; i < 17; i++)
	{
		if (f == g_ops[i].f)
			return (i);
	}
	return (0);
}

#include <stdio.h>

static void			run_next_process(t_area *area)
{
	t_process *process;

	process = ft_bheap_get(area->processes);
	SN_CYCLES = process->sleep;
	if (area->flags & STEP_DEBUG
		&& SN_CYCLES >= g_db_from
		&& process->f != g_ops[0].f)
	{
		char buff[10];
		fgets(buff, 9, stdin);
		printf("op: %s (%.2hhx)\nprocess_index: %u\nprocess_pc: %d\nop_byte: %hhu\nround: %d\n\n-> n_processes: %d:%lu\n",
				g_ops[func_index(process->f)].name,
				MAP[PC],
				process->ordinal_number,
				PC,
				MAP[PC],
				process->sleep,
				SN_PROCESS,
				area->processes->size(area->processes));
	}
	if (process->f != g_ops[0].f)
	{
		process->f(area, process);
		process->f = g_ops[0].f;
		process->sleep = SN_CYCLES + 1;
	}
	else
		process->f(area, process);

	//process->sleep = SN_CYCLES + get_process_sleep(process, MAP[PC]);
	move_first_process(area->processes);

}

static void			change_area_stats(t_area *area)
{
	if (SLIVES_IN_ROUND >= NBR_LIVE)
	{
		SDIE_CYCLE_DELTA -= CYCLE_DELTA;
		SNOT_CHANGED = 0;
	}
	else
		SNOT_CHANGED++;
	if (SNOT_CHANGED >= MAX_CHECKS)
	{
		SDIE_CYCLE_DELTA -= CYCLE_DELTA;
		SNOT_CHANGED = 0;
	}
	if (SDIE_CYCLE_DELTA < 0)
		SDIE_CYCLE_DELTA = 0;
	SDIE_CYCLE += SDIE_CYCLE_DELTA;
	SCYCLE_INROUND = 0;
	SLIVES_IN_ROUND = 0;
}

int32_t				play_game(t_area *area)
{
	area->win = area->g_stats.n_players - 1;
	while (SN_PROCESS > 0)
	{
		if ((area->flags & DUMP) != 0
			&& ((get_next_op_round(area->processes)) > SDUMP_CYCLE
			&& SDIE_CYCLE > SDUMP_CYCLE))
			print_dump(area);
		if ((get_next_op_round(area->processes)) > SDIE_CYCLE)
		{
			delete_not_live_processes(area);
			change_area_stats(area);
		}
		else
			run_next_process(area);
	}
	winner(area);
	return (0);
}
