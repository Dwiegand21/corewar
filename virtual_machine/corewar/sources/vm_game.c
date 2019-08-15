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
	int * const data = v->data;
	const int len = v->len;
	int i;

	i = 0;

	ft_timsort_int(data, len);

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

int32_t				play_game(t_area *area)
{
	register int	current_round;

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
				printf("%d\n", -1 * area->players[area->win].ordinal_number);
				free_args(&area);
				return (0);
			}
			if (current_round >= SDIE_CYCLE)
			{
				change_area_stats(area);
				area->n_die_cycle++;
			}
			if (timeout_time < time(0))
			{
				printf("0\n");
				free_args(&area);
				return (0);
			}
			area->current_index++;
			current_round++;
		}
	}
}
