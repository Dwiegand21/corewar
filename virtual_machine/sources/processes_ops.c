/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_ops.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 16:55:36 by dwiegand          #+#    #+#             */
/*   Updated: 2019/06/05 14:23:05 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void		load_process(t_area *area, t_list *processes)
{

}

void		new_process(t_list *processes, t_process *parent, uint32_t pc)
{
	t_process	*new;

	new = NULL;
	if (!(new = (t_process *)malloc(sizeof(t_process))))
		ft_error(ERR_ALLOC);
	*new = *parent;
	ft_lstadd(&processes, ft_lstnew(new, sizeof(new)));
}

void		delete_process(t_list *processes, t_list *node)
{

}

