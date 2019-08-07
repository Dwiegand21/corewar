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

int32_t				set_process_sleep(t_process *process, u_char byte)
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

int32_t			insert(t_process **head, t_process *process)
{
	t_process *cur;

	cur = *head;
	if (cur == NULL)
	{
		*head = process;
		process->next = NULL;
	}
	else if (process->ordinal_number >= cur->ordinal_number)
	{
		process->next = (*head);
		(*head) = process;
	}
	else
	{
		while (cur->next != NULL
			   && process->ordinal_number < cur->next->ordinal_number)
			cur = cur->next;
		process->next = cur->next;
		cur->next = process;
	}
	return (1);
}

// todo find all usages of INSERT and fix bug with next

//static int32_t			run_next_process(t_area *area)
static int32_t			run_next_round(t_area *area, t_process *lst)
{
	t_process *cur = lst;
	t_process *real_next;

	while (cur != NULL)
	{
		if (cur->n_lives >= area->n_die_cycle)
			cur->f(area, cur);
		cur = cur->next;
	}
	while (lst != NULL && ((real_next = lst->next) || true))
	{
		if (lst->n_lives < area->n_die_cycle)
		{
			lst->ordinal_number = 0;
			insert(&area->time[TIMELINE_SIZE], lst);
			SN_PROCESS--;
		}
		else
		{
			set_process_sleep(lst, area->map[lst->pc]);
			insert(&(area->time[(area->current_index + lst->sleep) % TIMELINE_SIZE]), lst);
		}
		lst = real_next;
	}
	area->time[area->current_index] = NULL;
	if (SN_PROCESS <= 0)
		return (0);
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

int 				ft_get_lst_size(t_process *lst)
{
	int size;

	size = 0;
	while (lst)
	{
		++size;
		lst = lst->next;
	}
	return (size);
}

#include <stdio.h>

void 				ft_print_timeline(t_process *time[TIMELINE_SIZE + 1], int curr_cycle, int prcs_count)
{
	int i;
	int lst_size;

	printf("%d(%d)>  ", curr_cycle, prcs_count);
	i = -1;
	while (++i < TIMELINE_SIZE + 1)
	{
		if ((lst_size = ft_get_lst_size(time[i])))
		{
			printf("%d:%d ", i, lst_size);
		}
//		if (ft_get_lst_size(time[i]))
//		{
//			printf("NOT empty!\n");
//		}
	}
	printf("\n");
}

static inline void	setup_init_processes(t_area *area, t_process *time[TIMELINE_SIZE + 1])
{
	int i;
	t_process **processes;

	i = -1;
	processes = area->init_processes;
	while (processes[++i])
	{
		time[processes[i]->sleep] = processes[i];
	}
}

// todo need %1001 instead of %1000 ??? - FIXED TO 1001

// note I insert to 749 position. II insert to

int32_t				play_game(t_area *area)
{
	register int	current_round;
//	register int	area->current_index;
	t_process		*time[TIMELINE_SIZE + 1] = { 0 };

	area->win = area->g_stats.n_players - 1;
	area->n_die_cycle = 0;
	area->time = time;

	current_round = 0;
	setup_init_processes(area, time);
	while (true)
	{

		area->current_index = 0;
		while (area->current_index < TIMELINE_SIZE)
		{
//			ft_print_timeline(time, current_round, area->g_stats.n_processes);
			if ((run_next_round(area, time[area->current_index])) == false)
			{
				winner(area);
				free_args(&area);
				exit(1);
			}
			if (current_round == SDIE_CYCLE)
			{
				change_area_stats(area);
				area->n_die_cycle++;
			}
			if (current_round == SDUMP_CYCLE)
			{
				print_dump(area);
				exit (1);
			}
			area->current_index++;
			current_round++;
		}
	}

//	area->win = area->g_stats.n_players - 1;
//	current_time = 0;
//	while (SN_PROCESS > 0)
//	{
//		if ((area->flags & DUMP) != 0
//			&& ((get_next_op_round(area->processes)) > SDUMP_CYCLE
//			&& SDIE_CYCLE > SDUMP_CYCLE))
//			print_dump(area);
//		if ((get_next_op_round(area->processes)) > SDIE_CYCLE)
//		{
//			delete_not_live_processes(area);
//			change_area_stats(area);
//		}
//		else
//			run_next_process(area);
//	}
//	winner(area);
	return (0);
}
