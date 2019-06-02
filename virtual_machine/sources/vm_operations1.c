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

void		next_op(t_area *area, t_process *process)
{
	PC = SHIFT(1);
}

void		live_op(t_area *area, t_process *process)
{
	int32_t		value;

	LIVE_S = true;
	value = be_get32(&PPC(1));

	if (value > -5 && value < 0)
		area->players[(~(value))].last_live = area->round;

	area->lives_in_round++;
	PC = SHIFT(6);
}

void		ld_op(t_area *area, t_process *process)
{
	if (DI_T(OCT00(PPC(1))) && R_T(OCT01(PPC(1))))
	{
		if (IS_REG(PPC(2 + ((D_T(OCT00(PPC(1))) == true) ? 4 : 2))))
		{
			if (I_T(OCT00(PPC(1))))
			{
				PREG[PPC(6) - 1] = be_get32(&PIPC(be_get16(&PPC(2))));
			}
			else
				PREG[PPC(6) - 1] = be_get32(&PPC(2));
			CARRY = ((PREG[PPC(6) - 1] == 0) ? true : false);
		}
	}
	PC = SHIFT(4 + ((D_T(OCT00(PPC(1))) == true) ? 4 : 2));
}

void		st_op(t_area *area, t_process *process)
{
	if (R_T(OCT00(PPC(1))) && RI_T(OCT01(PPC(1))))
	{
		if (IS_REG(PPC(2)))
		{
			if (R_T(OCT01(PPC(1))) && IS_REG(PPC(4)))
			{
				PREG[PPC(4) - 1] = PREG[PPC(2) - 1];
			}
			else
			{
				be_set32(&PIPC(be_get16(&PPC(4))), PPC(2));
			}
		}
	}
	PC = SHIFT(4 + ((R_T(OCT01(PPC(1))) == true) ? 1 : 2));
}

void		add_op(t_area *area, t_process *process)
{
	if (R_T(OCT00(PPC(1))) && R_T(OCT01(PPC(1))) && R_T(OCT02(PPC(1))))
	{
		if (IS_REG(PPC(2)) && IS_REG(PPC(6)) && IS_REG(PPC(10)))
		{
			PREG[PPC(10) - 1] = PREG[PPC(2) - 1] + PREG[PPC(6) - 1];
			CARRY = (PREG[PPC(10) - 1] == 0);
		}
	}
	PC = SHIFT(14);
}