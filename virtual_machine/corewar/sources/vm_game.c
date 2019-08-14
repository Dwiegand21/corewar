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

#define DBG 1

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

int 				ft_get_lst_size(t_process *lst)
{
	int size;

	size = 0;

	int c = 0;
	if (lst)
		c = 1;

	//if (c)
	//printf("\n>>>>   ");

	while (lst)
	{
		++size;
		//printf("%d ", lst->pc);
		lst = lst->next;
	}
	//if (c)
	//printf("\n");
	return (size);
}

int32_t			insert(t_process **head, t_process *process)
{
	t_process *cur;

	static int count = 0;
	static int big_lst_count = 0;

	if (head == 0)
	{
		printf("Insert called %d times\n", count);
		printf("Big_lst_count = %d\n", big_lst_count);
		return (0);
	}
	++count;

	//struct timespec tw = {0,1000};

	//nanosleep(&tw, 0);

	cur = *head;

	if (ft_get_lst_size(cur) > 1000)
		++big_lst_count;

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
	int was_next;
	int * const data = v->data;
	const int len = v->len;
	int i;

	i = len - 1;

	ft_timsort_int(data, len);

	while (i >= 0)
	{
		curr = &area->carriages->data[data[i]];

		if (curr->n_lives < area->n_die_cycle)
		{
			curr->f = 0;
			curr->ordinal_number = 0;
			SN_PROCESS--;
			--i;
		}
		else
		{
			if (DBG && curr->f != get_op && curr->f != next_op)
			{
				printf("P %d | %s\n", curr->ordinal_number + 1, find_cmd_name(curr->f));
				//printf("ACTION: %s {%d}\n", find_cmd_name(curr->f),
				//	   curr->ordinal_number + 1);
			}
			was_next = (curr->f == next_op);
			curr->f(area, curr);
//			if (was_next)
//				real_next = lst;
			if (!was_next)
			{
				ft_vm_vector_int_push_back((area->time + (area->current_index + curr->sleep) % TIMELINE_SIZE),
						curr->ordinal_number);
				//insert(&(area->time[(area->current_index + curr->sleep) % TIMELINE_SIZE]), curr);
				--i;
			}
		}
	}
//	while (lst != NULL)
//	{
//		real_next = lst->next;
//
//		if (lst->n_lives < area->n_die_cycle)
//		{
//			lst->f = 0;
//			lst->ordinal_number = 0;
//			lst->next = area->time[TIMELINE_SIZE];
//			area->time[TIMELINE_SIZE] = lst;
//			SN_PROCESS--;
//		}
//		else
//		{
//			//if (DBG)
//			//	printf("ACTION: %s {%d}\n", find_cmd_name(lst->f), lst->ordinal_number + 1);
//			was_next = lst->f == next_op;
//			lst->f(area, lst);
//			if (was_next)
//				real_next = lst;
//			else
//				insert(&(area->time[(area->current_index + lst->sleep) % TIMELINE_SIZE]), lst);
//		}
//		lst = real_next;
//	}
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

void 				ft_print_timeline(t_process *time[TIMELINE_SIZE + 1], int curr_cycle, int prcs_count)
{
	int i;
	int lst_size;
	int real_prcs_count;

	static int max_lst = 0;


	if (time == 0)
	{
		printf("Max lst_size = %d\n", max_lst);
		return ;
	}

//	printf("%d>  ", curr_cycle);
	i = -1;
	real_prcs_count = 0;
	while (++i < TIMELINE_SIZE)
	{
		if ((lst_size = ft_get_lst_size(time[i])))
		{
			if (lst_size > max_lst)
				max_lst = lst_size;
			//printf("%d:%d ", i, lst_size);
			real_prcs_count += lst_size;
		}
	}
	//printf(" (%d/%d) {%d processes are dead}\n", real_prcs_count, prcs_count,
	//		ft_get_lst_size(time[TIMELINE_SIZE]));
}

int32_t				play_game(t_area *area)
{
	register int	current_round;

	static int peak_processes = 0;

	area->win = area->g_stats.n_players - 1;
	area->n_die_cycle = 0;

	current_round = 0;
	while (true)
	{
		area->current_index = 0;
		while (area->current_index < TIMELINE_SIZE)
		{
//			if (DBG)
//				printf("%d> ", current_round);
//			if (DBG)
//				ft_print_timeline(area->time, current_round, area->g_stats.n_processes);
			if ((run_next_round(area, &area->time[area->current_index])) == false)
			{
				//insert(0, 0);
				//printf("Peak processes count: %d\n", peak_processes);
				//ft_print_timeline(0,0,0);
				winner(area);
				free_args(&area);
				return (0);
			}

			if (area->g_stats.n_processes > peak_processes)
				peak_processes = area->g_stats.n_processes;

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
			//if (area->current_index == TIMELINE_SIZE)
			//	area->current_index = 0;
			current_round++;
		}
	}
	return (0);
}
