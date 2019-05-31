/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 16:55:36 by dwiegand          #+#    #+#             */
/*   Updated: 2019/05/30 18:38:14 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

t_process*	start_node(uint32_t pc, int player_i)
{
	int32_t 	i;
	t_process	*new;

	new = NULL;
	if (!(new = malloc(sizeof(t_process))))
		ft_error(ERR_ALLOC);

	i = 1;
	while (i < REG_SIZE)
	{
		new->reg[i] = 0;
		i++;
	}
	new->pc = pc;
	new->reg[0] = player_i * -1;

	new->carry = false;
	new->live_in_session = false;

	new->sleep = 0;
	new->player = player_i;

	new->next = NULL;

	return (new);
}

void		push_node(t_process **root, t_process *new)
{
	if (*root != NULL)
		new->next = *root;
	*root = new;
}
