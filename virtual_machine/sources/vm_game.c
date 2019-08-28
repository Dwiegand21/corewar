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

static inline void		procede_one_carriage(
								t_area *area,
								int32_t const *data, int *i)
{
	t_process	*curr;
	int			wasnt_next;

	curr = &area->carriages->data[data[*i]];
	if (curr->n_lives < area->n_die_cycle)
	{
		SN_PROCESS--;
		++(*i);
	}
	else
	{
		wasnt_next = (curr->f != next_op);
		curr->f(area, &curr);
		if (wasnt_next)
		{
			ft_vm_vector_int_push_back((area->time +
				(area->current_index + curr->sleep) % TIMELINE_SIZE),
				curr->ordinal_number);
			++(*i);
		}
	}
}

static inline int32_t	run_next_round(t_area *area, t_vm_vector_int *v)
{
	int *const	data = v->data;
	const int	len = v->len;
	int			i;

	i = 0;
	ft_timsort_int(data, len);
	while (i < len)
		procede_one_carriage(area, data, &i);
	area->time[area->current_index].len = 0;
	if (SN_PROCESS <= 0)
		return (0);
	return (1);
}

static inline void		change_area_stats(t_area *area)
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
	SLIVES_IN_ROUND = 0;
}

static inline int32_t	one_cycle(t_area *area, register int current_round)
{
	if ((run_next_round(area, &area->time[area->current_index])) == false)
	{
		winner(area);
		free_args(area);
		return (0);
	}
	if (current_round == SDUMP_CYCLE)
	{
		print_dump(area);
		free_args(area);
		return (0);
	}
	if (current_round >= SDIE_CYCLE)
	{
		change_area_stats(area);
		area->n_die_cycle++;
	}
	area->current_index++;
	return (1);
}

void						play_game(t_area *area)
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
			if (!one_cycle(area, current_round))
				return ;
			current_round++;
		}
	}
}
