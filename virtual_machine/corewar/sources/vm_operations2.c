/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_operations2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 10:50:20 by axtazy            #+#    #+#             */
/*   Updated: 2019/06/13 18:42:40 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void		sub_op(t_area *area, t_process **carr) // dir_size = 4ca
{

	t_process	*process;

	process = *carr;
	if (R_T(OCT00) && R_T(OCT01) && R_T(OCT02))
	{
		if (IS_REG(PPC(2)) && IS_REG(PPC(3)) && IS_REG(PPC(4)))
		{
			PREG(PPC(4)) = PREG(PPC(2)) - PREG(PPC(3));
			CARRY = ((PREG(PPC(4)) == 0) ? true : false);
			area->champs_cmd_awared[process->player] +=
					area->map_owners[process->pc] == process->player;
		}
	}
	PC = SHIFT(2 + shift_size(PPC(1), 3, 4));
	process->f = get_op;
	process->sleep = 1;
	++area->champs_cmd_total[process->player];
}

void		and_op(t_area *area, t_process **carr) // dir_size = 4ca
{
	uint32_t	shift;
	int32_t		result;
	t_process	*process;

	process = *carr;

	shift = 2;
	if (RDI_T(OCT00) && RDI_T(OCT01) && R_T(OCT02)
		&& check_registers(area, process, 3, 4))
	{
		result = get_argument(area, process, &shift, OCT00);
		result &= get_argument(area, process, &shift, OCT01);
		PREG(PPC(shift)) = result;
		CARRY = ((result == 0) ? true : false);
		area->champs_cmd_awared[process->player] +=
				area->map_owners[process->pc] == process->player;
	}
	PC = SHIFT(2 + shift_size(PPC(1), 3, 4));
	process->f = get_op;
	process->sleep = 1;
	++area->champs_cmd_total[process->player];
}

void		or_op(t_area *area, t_process **carr) // dir_size = 4ca
{
	uint32_t	shift;
	int32_t		result;
	t_process	*process;

	process = *carr;

	shift = 2;
	if (RDI_T(OCT00) && RDI_T(OCT01) && R_T(OCT02)
		&& check_registers(area, process, 3, 4))
	{
		result = get_argument(area, process, &shift, OCT00);
		result |= get_argument(area, process, &shift, OCT01);
		PREG(PPC(shift)) = result;
		CARRY = ((result == 0) ? true : false);
		area->champs_cmd_awared[process->player] +=
				area->map_owners[process->pc] == process->player;
	}
	PC = SHIFT(2 + shift_size(PPC(1), 3, 4));
	process->f = get_op;
	process->sleep = 1;
	++area->champs_cmd_total[process->player];
}

void		xor_op(t_area *area, t_process **carr) // dir_size = 4ca
{
	uint32_t	shift;
	int32_t		result;
	t_process	*process;

	process = *carr;

	shift = 2;
	if (RDI_T(OCT00) && RDI_T(OCT01) && R_T(OCT02)
		&& check_registers(area, process, 3, 4))
	{
		result = get_argument(area, process, &shift, OCT00);
		result ^= get_argument(area, process, &shift, OCT01);
		PREG(PPC(shift)) = result;
		CARRY = ((result == 0) ? true : false);
		area->champs_cmd_awared[process->player] +=
				area->map_owners[process->pc] == process->player;
	}
	PC = SHIFT(2 + shift_size(PPC(1), 3, 4));
	process->f = get_op;
	process->sleep = 1;
	++area->champs_cmd_total[process->player];
}

void		zjmp_op(t_area *area, t_process **carr) // dir_size = 2
{
	t_process	*process;

	process = *carr;
	if (CARRY == true)
	{
		area->champs_cmd_awared[process->player] +=
				area->map_owners[process->pc] == process->player;
		PC = ISHIFT(((int32_t)get16(area, process, 1)));
	}
	else
		PC = SHIFT(3);
	process->f = get_op;
	process->sleep = 1;
	++area->champs_cmd_total[process->player];
}