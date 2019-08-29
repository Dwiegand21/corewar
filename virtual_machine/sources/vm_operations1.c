/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_operations1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 10:49:37 by axtazy            #+#    #+#             */
/*   Updated: 2019/08/29 13:23:47 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void		next_op(t_area *area, t_process **carr)
{
	t_process	*const process = *carr;

	if (area == NULL)
		return ;
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
	if ((value >= 0) && (value < (int32_t)SN_PLAYERS))
	{
		area->win = value;
	}
	printf("P %d | live %d\n", process->ordinal_number + 1, -(value + 1));
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
			printf("P %d | ld %d r%d\n", process->ordinal_number + 1, result, PPC(shift));
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
				int v = PPC(3);
				PREG(PPC(3)) = PREG(PPC(2));
				printf("P %d | st r%d %d\n", process->ordinal_number + 1, PPC(2), v);
			}
			else
			{
				int v = get16(area, process, 3) % IDX_MOD;
				set32(area, process, v , PREG(PPC(2)));
				printf("P %d | st r%d %d\n", process->ordinal_number + 1, PPC(2), v);
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
			printf("P %d | add r%d r%d r%d\n",
					process->ordinal_number + 1,
				   PPC(2),
				   PPC(3),
				   PPC(4));
			PREG(PPC(4)) = PREG(PPC(2)) + PREG(PPC(3));
			CARRY = (PREG(PPC(4)) == 0) ? true : false;
		}
	}
	PC = SHIFT(2 + shift_size(PPC(1), 3, 4));
	process->f = get_op;
	process->sleep = 1;
}
