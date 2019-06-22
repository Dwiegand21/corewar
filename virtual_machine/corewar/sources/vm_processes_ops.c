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

t_list		*delete_not_live_processes(t_area *area, t_list *root)
{
	t_list		*node;

	if (root == NULL)
		return (NULL);
	if (((t_process *)root->content)->live_in_session == true)
	{
		((t_process *)root->content)->live_in_session = false;
		root->next = delete_not_live_processes(area, root->next);
		return(root);
	}
	else
	{
		node = delete_not_live_processes(area, root->next);
		free(root);
		SN_PROCESS--;
		return (node);
	}
}

static t_list	*delete_elem(t_list *elem)
{
	t_list* next;

	next = elem->next;
	free(elem);
	return (next);
}

static t_list	*get_head_node(t_list *root, uint32_t *n_processes)
{
	t_list		*del;

	while (root != NULL
		&& ((t_process *)(root->content))->live_in_session == false)
	{
		del = root;
		root = root->next;
		free(del->content);
		free(del);
		(*n_processes)--;
	}
	return (root);
}

int32_t			delete_not_live_processes2(t_area *area)
{
	t_list	*cur;

	area->processes = get_head_node(area->processes, &SN_PROCESS);
	cur = area->processes;
	while (cur != NULL && cur->next != NULL)
	{
		if (((t_process *)cur->content)->live_in_session == true)
		{
			((t_process *)cur->content)->live_in_session = false;
		}
		else
		{
			cur->next = delete_elem(cur->next);
			SN_PROCESS--;
		}
		cur = cur->next;
	}
	return (1);
}