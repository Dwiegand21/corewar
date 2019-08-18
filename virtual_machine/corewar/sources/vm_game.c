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

#include <time.h>
#include "virtual_machine.h"

#define DBG 0

extern long timeout_time;

static int32_t			run_next_round(t_area *area, t_vm_vector_int *v)
{
	t_process *curr;
	int       wasnt_next;
	register int * const data = v->data;

	ft_timsort_int(data, v->len);
	register int i = 0;
	register int len = v->len;

	while (i < len)
	{
		curr = &area->carriages->data[data[i]];

		if (curr->n_lives < area->n_die_cycle)
		{
			curr->f = 0;
			curr->ordinal_number = 0;
			SN_PROCESS--;
			++i;
		}
		else
		{
			wasnt_next = (curr->f != next_op);
			curr->f(area, &curr);
			if (wasnt_next)
			{
				ft_vm_vector_int_push_back((area->time + (area->current_index + curr->sleep) % TIMELINE_SIZE),
						curr->ordinal_number);
				++i;
			}
		}
	}
	area->time[area->current_index].len = 0;
	if (SN_PROCESS <= 0)
	{
		return (0);
	}
	return (1);
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

#include <stdio.h>

int32_t				play_game(register t_area *area)
{
	int	current_round;

	area->win = area->g_stats.n_players - 1;
	area->n_die_cycle = 0;
	current_round = 0;

	while (true)
	{
		area->current_index = 0;
		while (area->current_index < TIMELINE_SIZE)
		{
			if ((run_next_round(area, &area->time[area->current_index])) == false)
			{
				printf("%d", area->win + 1);
				int endgame = area->players[
								(area->players[0].last_live > area->players[1].last_live ? 0 : 1)
								].last_live;
				if (area->our_champ >= 0)
					printf(" %f %d %d\n",
						(double)area->champs_cmd_awared[area->our_champ] /
						area->champs_cmd_total[area->our_champ],
						area->champs_agro[area->our_champ],
						endgame);
				else
					printf("\n");
				//printf("1 %d\n2 %d\n", area->champs_agro[0], area->champs_agro[1]);
//				write(1, area->win == 0 ? "1\n" : "2\n", 2);
//				printf("Player 1 awareness: %f (%d/%d)\n",
//					   (double)area->champs_cmd_awared[0] / area->champs_cmd_total[0],
//					   area->champs_cmd_awared[0], area->champs_cmd_total[0]);
//				printf("Player 2 awareness: %f (%d/%d)\n",
//					   (double)area->champs_cmd_awared[1] / area->champs_cmd_total[1],
//					   area->champs_cmd_awared[1], area->champs_cmd_total[1]);
//				printf("Last cycle: %d\n",
//					   area->players[
//					   		(area->players[0].last_live > area->players[1].last_live ? 0 : 1)
//					   		].last_live);
				free_args(area);
				return (0);
			}
			if (current_round >= SDIE_CYCLE)
			{
				change_area_stats(area);
				area->n_die_cycle++;
			}
			if (timeout_time < time(0))
			{
				write(1, "0\n", 2);
				free_args(area);
				return (0);
			}
			++area->current_index;
			area->g_stats.n_cycles = ++current_round;
		}
	}
}
