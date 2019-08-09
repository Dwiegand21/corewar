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

#define DBG 0

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

static int32_t			run_next_round(t_area *area, t_process *lst)
{
	t_process *real_next = lst;
	int was_next;

	while (lst != NULL)
	{
		real_next = lst->next;

		if (lst->n_lives < area->n_die_cycle)
		{
			lst->f = 0;
			lst->ordinal_number = 0;
			lst->next = area->time[TIMELINE_SIZE];
			area->time[TIMELINE_SIZE] = lst;
			SN_PROCESS--;
		}
		else
		{
			if (DBG)
				printf("ACTION: %s {%d}\n", find_cmd_name(lst->f), lst->ordinal_number + 1);
			was_next = lst->f == next_op;
			lst->f(area, lst);
			if (was_next)
				real_next = lst;
			else
				insert(&(area->time[(area->current_index + lst->sleep) % TIMELINE_SIZE]), lst);
			//lst->f = get_op;
			//lst->sleep = 1;
		}
		lst = real_next;
	}
	/*while (lst != NULL)
	{
		cur = lst->next;
		if (lst->n_lives < area->n_die_cycle)
		{
			lst->ordinal_number = 0;
			lst->next = area->time[TIMELINE_SIZE];
			area->time[TIMELINE_SIZE] = lst;
			//insert(&area->time[TIMELINE_SIZE], lst);
			SN_PROCESS--;
		}
		else
		{
			set_process_op_and_sleep2(lst, area->map[lst->pc]);
			insert(&(area->time[(area->current_index + lst->sleep) % TIMELINE_SIZE]), lst);
		}
		lst = cur;
	}*/
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

#include <stdio.h>

void 				ft_print_timeline(t_process *time[TIMELINE_SIZE + 1], int curr_cycle, int prcs_count)
{
	int i;
	int lst_size;
	int real_prcs_count;

//	printf("%d>  ", curr_cycle);
	i = -1;
	real_prcs_count = 0;
	while (++i < TIMELINE_SIZE)
	{
		if ((lst_size = ft_get_lst_size(time[i])))
		{
			printf("%d:%d ", i, lst_size);
			real_prcs_count += lst_size;
		}
	}
	printf(" (%d/%d) {%d processes are dead}\n", real_prcs_count, prcs_count,
			ft_get_lst_size(time[TIMELINE_SIZE]));
}



// need %1001 instead of %1000 ??? - FIXED TO 1001
// two extra processes appears in 4626 - OK
// need to kill at 4608 (2 carriages killed, 9 left) - OK
// note extra sti at 6115 (109 at timeline). Appears after 6090

// note Asmobre.cor:4558 - 3 processes die in original vw
// 		note> in our vm no processes die in that turn. 1 process dies at 4567

static void
print_timemap(t_area *area)
{
	t_process *p;

//	for (int i = 0; i < TIMELINE_SIZE; i++)
//	{
//
//		if (area->time[i] != NULL)
//		{
			//printf("[%d]:", i);
			//p = area->time[i];
			p = area->time[area->current_index];
			while (p != NULL)
			{
				printf(" %d :: %d\n", p->ordinal_number, p->n_lives);
				p = p->next;
			}
			printf("\n");
//		}
//
//	}
	printf("processes: %d\nn_die: %d\n", SN_PROCESS, area->n_die_cycle);
	char c;
	scanf("%c", &c);
}

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
			if (DBG)
				printf("%d> ", current_round);
			if (DBG)
				ft_print_timeline(area->time, current_round, area->g_stats.n_processes);
			if ((run_next_round(area, area->time[area->current_index])) == false)
			{
				winner(area);
				free_args(&area);
				exit(1);
			}

			if (current_round == SDUMP_CYCLE)
			{
				if (!DBG)
					print_dump(area);
				exit (1);
			}

			if (current_round >= SDIE_CYCLE)
			{
				change_area_stats(area);
				area->n_die_cycle++;
			}
			area->current_index++;
			current_round++;
		}
	}
}
