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

//int32_t				get_process_sleep(t_process *process, u_char byte)
//{
//	if (byte > 0 && byte < 17)
//	{
//		process->f = g_ops[byte].f;
//		return (g_ops[byte].sleep);
//	}
//	else
//	{
//		process->f = NULL;
//		return (1);
//	}
//}

//static int			func_index(void (*f)(t_area *, t_process *))
//{
//	for (int i = 0; i < 17; i++)
//	{
//		if (f == g_ops[i].f)
//			return (i);
//	}
//	return (0);
//}

/*
int32_t			delete_not_live_processes2(t_area *area)
{
	t_list	*prew;
	t_list	*cur;

	area->processes = get_head_node(area->processes, &SN_PROCESS);
	area->processes = get_head_node(area->processes);
//	if (area->processes == NULL)
//		return (0);
	cur = area->processes;
	while (cur != NULL && cur->next != NULL)
	prew = NULL;
	while (cur != NULL)
	{
		if (((t_process *)cur->content)->live_in_session == true)
		{
			((t_process *)cur->content)->live_in_session = false;
			prew = cur;
			cur = cur->next;
		}
		else
		{
			cur->next = delete_elem(cur->next);
			cur = cur->next;
			free(prew->next->content);
			free(prew->next);
			prew->next = cur;
			SN_PROCESS--;
		}
		cur = cur->next;
	}
	return (1);
}
 */

int32_t				get_process_sleep(t_process *process, u_char byte)
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

static int32_t			insert(t_process **head, t_process *process)
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

//static int32_t			run_next_process(t_area *area)
static int32_t			run_next_round(t_area *area, t_process *lst)
{
	t_process *cur = lst;

	while (cur != NULL)
	{
		if (cur->n_lives >= area->n_die_cycle)
			cur->f(area, cur);
		cur = cur->next;
	}
	while (lst != NULL)
	{
		if (lst->n_lives < area->n_die_cycle)
		{
			lst->ordinal_number = 0;
			insert(&area->time[1000], lst);
			SN_PROCESS--;
		}
		else
		{
			get_process_sleep(lst, area->map[lst->pc]);
			insert(&area->time[(area->current_index + lst->sleep) % 1000], lst);
		}
		lst = lst->next;
	}
	area->time[area->current_index] = NULL;
	if (SN_PROCESS <= 0)
		return (0);
	return (1);

//	t_process *process;
//
//
//	process = ft_bheap_get(area->processes);
//	SN_CYCLES = process->sleep;
//	if (area->flags & STEP_DEBUG
//		&& SN_CYCLES >= g_db_from
//		&& process->f != g_ops[0].f)
//	{
//		char buff[10];
//		fgets(buff, 9, stdin);
//		printf("op: %s (%.2hhx)\nprocess_index: %u\nprocess_pc: %d\nop_byte: %hhu\nround: %d\n\n-> n_processes: %d:%lu\n",
//				g_ops[func_index(process->f)].name,
//				MAP[PC],
//				process->ordinal_number,
//				PC,
//				MAP[PC],
//				process->sleep,
//				SN_PROCESS,
//				area->processes->size(area->processes));
//	}
//	if (process->f != g_ops[0].f)
//	{
//		process->f(area, process);
//		process->f = g_ops[0].f;
//		process->sleep = SN_CYCLES + 1;
//	}
//	else
//		process->f(area, process);
//
//	//process->sleep = SN_CYCLES + get_process_sleep(process, MAP[PC]);
//	move_first_process(area->processes);
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
	register int	current_round;
//	register int	area->current_index;
	t_process		*time[1001] = { 0 };

	area->win = area->g_stats.n_players - 1;
	area->n_die_cycle = 0;
	area->time = time;

	current_round = 0;
	while (true)
	{
		area->current_index = 0;
		while (area->current_index < 1000)
		{
			if (current_round == SDUMP_CYCLE)
			{
				print_dump(area);
			}
			if ((run_next_round(area, time[area->current_index])) == false)
			{
				winner(area);
				free_args(&area);
				exit(1);
			}
			if (area->current_index == SDIE_CYCLE)
			{
				change_area_stats(area);
				area->n_die_cycle++;
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
