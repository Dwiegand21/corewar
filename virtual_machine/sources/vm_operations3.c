/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_operations3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 10:50:49 by axtazy            #+#    #+#             */
/*   Updated: 2019/08/29 15:54:34 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void		ldi_op(t_area *area, t_process **carr)
{
	int32_t				result;
	uint32_t			shift;
	t_process *const	process = *carr;

	shift = 2;
	if (RDI_T(OCT00) && RD_T(OCT01) && R_T(OCT02)
		&& check_registers(area, process, 3, 2))
	{
		int v1 = get_argument2(area, process, &shift, OCT00);
		int v2 = get_argument2(area, process, &shift, OCT01);

		result =  v1;
		result += v2;

		if (IS_REG(PPC(shift)))
		{
			printf("P %d | ldi %d %d r%d\n",
					process->ordinal_number + 1, v1, v2, PPC(shift));
			PREG(PPC(shift)) = get32(area, process, result % IDX_MOD);
		}
	}
	PC = SHIFT(2 + shift_size(PPC(1), 3, 2));
	process->f = get_op;
	process->sleep = 1;
}

void		sti_op(t_area *area, t_process **carr)
{
	int32_t				result;
	uint32_t			shift;
	uint32_t			fshift;
	t_process *const	process = *carr;

	shift = 3;
	fshift = shift_size(PPC(1), 3, 2);
	if (R_T(OCT00) && RDI_T(OCT01) && RD_T(OCT02)
		&& check_registers(area, process, 3, 2))
	{
		int v1 = get_argument2(area, process, &shift, OCT01);
		int v2 = get_argument2(area, process, &shift, OCT02);

		printf("P %d | sti r%d %d %d\n",
				process->ordinal_number + 1, PPC(2), v1, v2);
		fflush(stdout);
		result =  v1;
		result += v2;
		set32(area, process, result % IDX_MOD, PREG(PPC(2)));
	}
	PC = SHIFT(2 + fshift);
	process->f = get_op;
	process->sleep = 1;
}

void		fork_op(t_area *area, t_process **carr)
{
	int32_t		result;
	t_process	*process;
	int			process_id;
	t_process	backup;

	process = *carr;
	backup = *process;
	process_id = process->ordinal_number;
	result = get16(area, process, 1);
	new_process(area, &backup, result % IDX_MOD);
	process = area->carriages->data + process_id;
	printf("P %d | fork %d\n", process->ordinal_number + 1, result);
	PC = SHIFT(3);
	process->f = get_op;
	process->sleep = 1;
	*carr = process;
}

void		lld_op(t_area *area, t_process **carr)
{
	int32_t				result;
	uint32_t			shift;
	t_process *const	process = *carr;

	shift = 2;
	if (DI_T(OCT00) && R_T(OCT01))
	{
		if (I_T(OCT00))
		{
			result = (get32(area, process, get16(area, process, shift)));
			result = OP_1;
			shift += 2;
		}
		else
			result = get_argument(area, process, &shift, OCT00);

		if (IS_REG(PPC(shift)))
		{
			printf("P %d | lld %d r%d\n", process->ordinal_number + 1, result, PPC(shift));
			PREG(PPC(shift)) = result;
//			PREG(PPC(shift)) = (result >> 16) & 0xFFFF; // ???
//			PREG(PPC(shift)) = result;
			CARRY = ((result == 0) ? true : false);
		}
	}
	PC = SHIFT(2 + shift_size(PPC(1), 2, 4));
	process->f = get_op;
	process->sleep = 1;
}

void		lldi_op(t_area *area, t_process **carr)
{
	int32_t				result;
	uint32_t			shift;
	t_process *const	process = *carr;

	shift = 2;
	if (RDI_T(OCT00) && RD_T(OCT01) && R_T(OCT02)
		&& check_registers(area, process, 3, 2))
	{
		if (I_T(OCT00))
		{
			result = OP_2;
//			result = get_argument2(area, process, &shift, OCT00);
//			result = (get32(area, process, get16(area, process, shift)));
			shift += 2;
		}
		else
			result = get_argument2(area, process, &shift, OCT00);

		int v1 = result;
		int v2 = get_argument2(area, process, &shift, OCT01);

		result += v2;
		if (IS_REG(PPC(shift)))
		{
			printf("P %d | lldi %d %d r%d\n", process->ordinal_number + 1, v1, v2, PPC(shift));
			PREG(PPC(shift)) = get32(area, process, result);
			CARRY = (PREG(PPC(shift)) == 0) ? true : false;
		}
	}
	PC = SHIFT(2 + shift_size(PPC(1), 3, 2));
	process->f = get_op;
	process->sleep = 1;
}