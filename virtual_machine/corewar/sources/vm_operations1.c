/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_operations1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 10:49:37 by axtazy            #+#    #+#             */
/*   Updated: 2019/06/12 14:23:41 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void		next_op(t_area *area, t_process *process) // dir_size = 4
{
	PC = SHIFT(1);
}

void		live_op(t_area *area, t_process *process) // dir_size = 4
{
	int32_t		value;

	LIVE_S = true;
	value = get32(area, process, 1);

	if (value > -5 && value < 0)
		area->players[(~(value))].last_live = SN_CYCLES;

	SLIVES_IN_ROUND++;
	PC = SHIFT(5);
}

void		ld_op(t_area *area, t_process *process) // dir_size = 4ca
{
	uint32_t	shift;
	int32_t 	result;

	shift = 2;
	if (DI_T(OCT00) && R_T(OCT01))
	{
		result = get_argument(area, process, &shift, OCT00);
//		if (I_T(OCT00))
//			result %= IDX_MOD;
		if (IS_REG(PPC(shift)))
		{
			PREG(PPC(shift)) = result;
			CARRY = ((result == 0) ? true : false);
		}
	}
	PC = SHIFT(2 + shift_size(PPC(1), 2, 4));
}

void		st_op(t_area *area, t_process *process) // dir_size = 4a
{
	uint32_t	shift;

	shift = shift_size(PPC(1), 2, 4);
	if (R_T(OCT00) && RI_T(OCT01))
	{
		if (IS_REG(PPC(2)))
		{
			if (R_T(OCT01) && IS_REG(PPC(3)))
			{
				PREG(PPC(3)) = PREG(PPC(2));
			}
			else
			{
				set32(area, process,
						get16(area, process, 3) % IDX_MOD, PREG(PPC(2)));
			}
		}
	}
	PC = SHIFT(2 + shift);
}

void		add_op(t_area *area, t_process *process) // dir_size = 4ca
{
	if (R_T(OCT00) && R_T(OCT01) && R_T(OCT02))
	{
		if (IS_REG(PPC(2)) && IS_REG(PPC(3)) && IS_REG(PPC(4)))
		{
			PREG(PPC(4)) = PREG(PPC(2)) + PREG(PPC(3));
			CARRY = (PREG(PPC(4)) == 0);
		}
	}
	PC = SHIFT(2 + shift_size(PPC(1), 3, 4));
}