/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_game_NEW.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 17:23:31 by dwiegand          #+#    #+#             */
/*   Updated: 2019/06/30 17:23:31 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

//static void			init_process_op_NEW(t_area *area, t_process *process)
//{
//	if (PPC(0) > 0 && PPC(0) < 17)
//	{
//		process->f = g_ops[PPC(0)].f;
//		process->sleep = g_ops[PPC(0)].sleep - 1;
//	}
//	else
//	{
//		process->f = g_ops[0].f;
//		process->sleep = g_ops[0].sleep - 1;
//	}
//}
//
//static int32_t 		play_round_NEW(t_area *area)
//{
//	t_list		*cur;
//
//	cur = area->processes;
//	while (cur != NULL)
//	{
//		if (((t_process *)cur->content)->f == NULL)
//			init_process_op_NEW(area, ((t_process *)cur->content));
//		if (((t_process *)cur->content)->sleep == 0)
//		{
//			(((t_process *)cur->content)->f)(area, ((t_process *)cur->content));
//			((t_process *)cur->content)->f = NULL;
//		}
//		else
//			((t_process *)cur->content)->sleep--;
//		cur = cur->next;
//	}
//	return (0);
//}
//
//static void			change_area_stats_NEW(t_area *area)
//{
////	printf("round: %d : %d : %d : %d\n", SN_CYCLES, SDIE_CYCLE, SNOT_CHANGED, SLIVES_IN_ROUND);
//	if (SLIVES_IN_ROUND >= NBR_LIVE)
//	{
//		SDIE_CYCLE -= CYCLE_DELTA;
//		SNOT_CHANGED = 0;
//	}
//	else
//		SNOT_CHANGED++;
//	if (SNOT_CHANGED >= MAX_CHECKS)
//		SDIE_CYCLE -= CYCLE_DELTA;
//	SCYCLE_INROUND = 0;
//	SLIVES_IN_ROUND = 0;
//}
//
void				winner_NEW(t_area *area)
{
	printf("Contestant %d, \"%s\", has won !\n",
			area->players[area->win].ordinal_number,
			area->players[area->win].name);
	fflush(stdout);
}
//
//int32_t				play_game_NEW(t_area *area)
//{
//	area->win = area->g_stats.n_players - 1;
//	while (area->processes != NULL)
//	{
//		if (SDUMP_CYCLE == SN_CYCLES)
//			print_dump(area);
//		SN_CYCLES++;
//		SCYCLE_INROUND++;
//		play_round_NEW(area);
//		if (SCYCLE_INROUND >= SDIE_CYCLE)
//		{
//			delete_not_live_processes(area);
//			change_area_stats_NEW(area);
//		}
//	}
//	winner_NEW(area);
//	return (0);
//}

int32_t				play_game_NEW(t_area *area)
{
	area->win = area->g_stats.n_players - 1;
	while (area->processes != NULL)
	{
		if ()
	}
	winner_NEW(area);
	return (0);
}