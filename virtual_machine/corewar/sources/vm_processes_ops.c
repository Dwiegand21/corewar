/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_processes_ops.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 16:55:36 by dwiegand          #+#    #+#             */
/*   Updated: 2019/06/10 04:28:25 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void		load_process(t_area *area, int32_t player, uint32_t pc)
{
	t_process	*new;

	new = NULL;
	if (!(new = (t_process *)ft_memalloc(sizeof(t_process))))
		ft_error(ERRALLOC, __func__);
	new->player = (int32_t)player;
	new->reg[0] = ~player;
	new->pc = pc;
	ft_lstadd(&area->processes, ft_lstnew(new, sizeof(*new)));
	SN_PROCESS++;
}

void		new_process(t_area *area, t_process *process, uint32_t pc)
{
	t_process	*new;

	new = NULL;
	if (!(new = (t_process *)malloc(sizeof(t_process))))
		ft_error(ERRALLOC, __func__);
	*new = *process;
	new->pc = SHIFT(pc);
	new->f = NULL;
	ft_lstadd(&area->processes, ft_lstnew(new, sizeof(*new)));
	SN_PROCESS++;
}

static t_list	*get_head_node(t_list *root)
{
	t_list		*del;

	while (root != NULL
		&& ((t_process *)root->content)->live_in_session == false)
	{
		del = root;
		root = root->next;
		free(del->content);
		free(del);
	}
	return (root);
}

int32_t			delete_not_live_processes(t_area *area)
{
	t_list	*prew;
	t_list	*cur;

	area->processes = get_head_node(area->processes);
	cur = area->processes;
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
			cur = cur->next;
			free(prew->next->content);
			free(prew->next);
			prew->next = cur;
			SN_PROCESS--;
		}
	}
	return (1);
}
