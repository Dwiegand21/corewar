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

int is_ok = 0;

static void			winner(t_area *area)
{
	printf("Contestant %d, \"%s\", has won !\n",
			area->players[area->win].ordinal_number,
			area->players[area->win].name);
	fflush(stdout);
}

int32_t				set_process_op_and_sleep(t_process *process, u_char byte)
{
	if (byte > 0 && byte < 17)
	{
		process->f = g_ops[byte].f;
		process->sleep = g_ops[byte].sleep;
	}
	else
	{
		process->f = g_ops[0].f;
		process->sleep = g_ops[0].sleep;
	}
	return (1);
}

//int32_t			insert(t_process **head, t_process *process)
//{
//	t_process *cur;
//
//	static int count = 0;
//	static int big_lst_count = 0;
//
//	if (head == 0)
//	{
//		printf("Insert called %d times\n", count);
//		printf("Big_lst_count = %d\n", big_lst_count);
//		return (0);
//	}
//	++count;
//
//	//struct timespec tw = {0,1000};
//
//	//nanosleep(&tw, 0);
//
//	cur = *head;
//
//	if (ft_get_lst_size(cur) > 1000)
//		++big_lst_count;
//
//	if (cur == NULL)
//	{
//		*head = process;
//		process->next = NULL;
//	}
//	else if (process->ordinal_number >= cur->ordinal_number)
//	{
//		process->next = (*head);
//		(*head) = process;
//	}
//	else
//	{
//		while (cur->next != NULL
//			   && process->ordinal_number < cur->next->ordinal_number)
//			cur = cur->next;
//		process->next = cur->next;
//		cur->next = process;
//	}
//	return (1);
//}

static inline char		*find_cmd_name(void	(*f)())
{
	int i = -1;
	while (++i < 19)
	{
		if (f == g_ops[i].f)
		{
			return g_ops[i].name;
		}
	}
	return (NULL);
}

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
//			if (DBG && curr->f != get_op && curr->f != next_op)
//			{
//				printf("P %d | %s\n", curr->ordinal_number + 1, find_cmd_name(curr->f));
//				printf("ACTION: %s {%d}\n", find_cmd_name(curr->f),
//					   curr->ordinal_number + 1);
//			}
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

	static int death_count = 0;
	static int peak_processes = 0;

	while (true)
	{
		area->current_index = 0;
		while (area->current_index < TIMELINE_SIZE)
		{
//			if (DBG)
//				printf("%d> ", current_round);
//			if (DBG)
//				ft_print_timeline(area->time, current_round, area->g_stats.n_processes);
///			if (area->g_stats.n_processes > peak_processes)
///			{
///				peak_processes = area->g_stats.n_processes;
///				death_count = area->carriages->len - peak_processes;
///			}
			if ((run_next_round(area, &area->time[area->current_index])) == false)
			{
				winner(area);

				///printf("Peak processes %d, Dead count: %d\n", peak_processes, death_count);

				free_args(&area); // todo uncomment it
				return (0);
			}
			if (current_round == SDUMP_CYCLE)
			{
				if (!DBG)
					print_dump(area);
				return (0);
			}
//			if (DBG)
//				printf("\n");
			if (current_round >= SDIE_CYCLE)
			{
				change_area_stats(area);
				area->n_die_cycle++;
			}
			area->current_index++;
			current_round++;
		}
	}
	return (0);
}
