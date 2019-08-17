/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_operations1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 10:49:37 by axtazy            #+#    #+#             */
/*   Updated: 2019/07/03 20:21:48 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void		next_op(t_area *area, t_process **carr)
{
	t_process	*const process = *carr;

	PC = SHIFT(1);
	process->f = get_op;
	process->sleep = 1;
}

void		live_op(t_area *area, t_process **carr)
{
	int32_t				value;
	t_process *const	process = *carr;

	process->n_lives = area->n_die_cycle + 1;
	value = -get32(area, process, 1) - 1;
	if (value >= 0 && value < SN_PLAYERS)
	{
		area->players[value].last_live = SN_CYCLES;
		area->win = value;
	}
	SLIVES_IN_ROUND++;
	PC = SHIFT(5);
	process->f = get_op;
	process->sleep = 1;
}

void		ld_op(t_area *area, t_process **carr)
{
	uint32_t			shift;
	int32_t				result;
	t_process *const	process = *carr;

	shift = 2;
	if (DI_T(OCT00) && R_T(OCT01))
	{
		result = get_argument(area, process, &shift, OCT00);
		if (IS_REG(PPC(shift)))
		{
			PREG(PPC(shift)) = result;
			CARRY = ((result == 0) ? true : false);
		}
	}
	PC = SHIFT(2 + shift_size(PPC(1), 2, 4));
	process->f = get_op;
	process->sleep = 1;
}

void		st_op(t_area *area, t_process **carr)
{
	uint32_t			shift;
	t_process *const	process = *carr;

	shift = shift_size(PPC(1), 2, 4);
	if (R_T(OCT00) && RI_T(OCT01)
	&& check_registers(area, process, 2, 4))
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
	process->f = get_op;
	process->sleep = 1;
}

void		add_op(t_area *area, t_process **carr)
{
	t_process *const process = *carr;

	if (R_T(OCT00) && R_T(OCT01) && R_T(OCT02))
	{
		if (IS_REG(PPC(2)) && IS_REG(PPC(3)) && IS_REG(PPC(4)))
		{
			PREG(PPC(4)) = PREG(PPC(2)) + PREG(PPC(3));
			CARRY = (PREG(PPC(4)) == 0) ? true : false;
		}
	}
	PC = SHIFT(2 + shift_size(PPC(1), 3, 4));
	process->f = get_op;
	process->sleep = 1;
}
