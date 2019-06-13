/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 15:29:09 by axtazy            #+#    #+#             */
/*   Updated: 2019/06/13 22:08:50 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

static void			init_process_op(t_area *area, t_process *process)
{
	if (PPC(0) > 0 && PPC(0) < 17)
	{
		process->f = g_ops[PPC(0)].f;
		process->sleep = g_ops[PPC(0)].sleep - 1;
	}
	else
	{
		process->f = g_ops[0].f;
		process->sleep = g_ops[0].sleep - 1;
	}
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

static void			change_area_stats(t_area *area)
{
//	printf("round: %d : %d : %d : %d\n", SN_CYCLES, SDIE_CYCLE, SNOT_CHANGED, SLIVES_IN_ROUND);
	if (SLIVES_IN_ROUND >= NBR_LIVE)
	{
		SDIE_CYCLE -= CYCLE_DELTA;
		SNOT_CHANGED = 0;
	}
	else
		SNOT_CHANGED++;
	if (SNOT_CHANGED >= MAX_CHECKS)
		SDIE_CYCLE -= CYCLE_DELTA;
//	if (SDIE_CYCLE < 0)			// ???
//		SDIE_CYCLE = 0;
	SCYCLE_INROUND = 0;
	SLIVES_IN_ROUND = 0;
}

void				winner(t_area *area)
{
	int player = -1;
	int last = -1;
	for (int i = 0; i < area->g_stats.n_players; i++)
	{
		if (area->players[i].last_live > last)
		{
			player = i;
			last = area->players[i].last_live;
		}
	}
	printf("Contestant %d, \"%s\", has won !\n",
		   area->players[player].ordinal_number,
		   area->players[player].name);
}

int32_t				play_game(t_area *area)
{
	while (SN_PROCESS)
	{
		if (SDUMP_CYCLE == SN_CYCLES)
			print_dump(area);
		SN_CYCLES++;
		SCYCLE_INROUND++;
		play_round(area);
		if (SCYCLE_INROUND >= SDIE_CYCLE)
		{
			area->processes = delete_not_live_processes(area, area->processes);
			change_area_stats(area);
		}
	}
//	printf("last round: %d\n", SN_CYCLES);
//	for(int i = 0;i < SN_PLAYERS;i++)
//	{
//		printf(">> Player%d(%u): %8d <<\n", i,
//											APLAYER(i).ordinal_number,
//											APLAYER(i).last_live);
//	}
	winner(area);
	return (0);
}