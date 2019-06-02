/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_operations1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 10:49:37 by axtazy            #+#    #+#             */
/*   Updated: 2019/06/02 05:55:12 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void		next_op(t_area *area, t_process *p)
{
	p->pc = area->map[(p->pc + 1) % MEM_SIZE];
}

void		live_op(t_area *area, t_process *p)
{

}

void		ld_op(t_area *area, t_process *p)
{

}

void		st_op(t_area *area, t_process *p)
{

}

void		add_op(t_area *area, t_process *p)
{

}