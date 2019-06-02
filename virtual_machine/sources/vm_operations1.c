/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_operations1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 10:49:37 by axtazy            #+#    #+#             */
/*   Updated: 2019/06/02 15:15:57 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void		next_op(t_area *area, t_process *p)
{
	p->pc = area->map[(p->pc + 1) % MEM_SIZE];
}

void		live_op(t_area *area, t_process *p)
{
	int32_t		value;

	p->live_in_session = true;
	value = be_get32(area + p->pc + 1);

	if (value > -5 && value < 0)
		area->players[(~(value))].last_live = area->round;

	area->lives_in_round++;
	p->pc = SHIFT(p->pc, 5);
}

void		ld_op(t_area *area, t_process *p)
{
	if (DI_T(OCT00(MAP(p->pc + 1))) && R_T(OCT01(MAP(p->pc + 1))))
	{
		if (IS_REG(MAP(p->pc + 6)))
		{
			if (I_T(OCT00(MAP(p->pc + 1))))
			{
				;
			}
		}
	}
}

void		st_op(t_area *area, t_process *p)
{

}

void		add_op(t_area *area, t_process *p)
{

}