/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_ops.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 16:55:36 by dwiegand          #+#    #+#             */
/*   Updated: 2019/06/05 17:38:37 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void		load_process(t_area *area, int32_t player, uint32_t pc)
{
	t_process	*new;

	new = NULL;
	if (!(new = (t_process *)ft_memalloc(sizeof(t_process))))
		ft_error(ERR_ALLOC);
	new->player = (int32_t)player;
	new->reg[0] = ~player;
	new->pc = pc;
	ft_lstadd(&area->processes, ft_lstnew(new, sizeof(*new)));
	area->n_processes++;
}

void		new_process(t_area *area, t_process *process, uint32_t pc)
{
	t_process	*new;

	new = NULL;
	if (!(new = (t_process *)malloc(sizeof(t_process))))
		ft_error(ERR_ALLOC);
	*new = *process;
	new->pc = SHIFT(pc);
	new->f = NULL;
	ft_lstadd(&area->processes, ft_lstnew(new, sizeof(*new)));
	area->n_processes++;
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
		area->n_processes--;
		return (node);
	}
}

