/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_operations1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 10:49:37 by axtazy            #+#    #+#             */
/*   Updated: 2019/06/05 13:45:47 by axtazy           ###   ########.fr       */
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
		area->players[(~(value))].last_live = area->round;

	area->lives_in_round++;
	PC = SHIFT(6);
}

void		ld_op(t_area *area, t_process *process) // dir_size = 4ca
{
	uint32_t	shift;
	int32_t 	result;

	shift = 2;
	if (DI_T(OCT00) && R_T(OCT01))
	{
		result = get_argument(area, process, &shift, OCT00);
		if (I_T(OCT00))
			result %= IDX_MOD;
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
	PC = SHIFT(2 + shift_size(PPC(1), 2, 4));
}

void		add_op(t_area *area, t_process *process) // dir_size = 4ca
{
	if (R_T(OCT00) && R_T(OCT01) && R_T(OCT02))
	{
		if (IS_REG(PPC(2)) && IS_REG(PPC(6)) && IS_REG(PPC(10)))
		{
			PREG(PPC(10)) = PREG(PPC(2)) + PREG(PPC(6));
			CARRY = (PREG(PPC(10)) == 0);
		}
	}
	PC = SHIFT(14);
}