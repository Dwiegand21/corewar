/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_operations2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 10:50:20 by axtazy            #+#    #+#             */
/*   Updated: 2019/06/05 17:44:05 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void		sub_op(t_area *area, t_process *process) // dir_size = 4ca
{
	if (R_T(OCT00) && R_T(OCT01) && R_T(OCT02))
	{
		if (IS_REG(PPC(2)) && IS_REG(PPC(6)) && IS_REG(PPC(10)))
		{
			PREG(PPC(10)) = PREG(PPC(2)) - PREG(PPC(6));
			CARRY = ((PREG(PPC(10)) == 0) ? true : false);
		}
	}
	PC = SHIFT(14);
}

void		and_op(t_area *area, t_process *process) // dir_size = 4ca
{
	uint32_t	shift;
	int32_t		result;

	shift = 2;
	if (RDI_T(OCT00) && RDI_T(OCT01) && R_T(OCT02))
	{
		result = get_argument(area, process, &shift, OCT00);
		result &= get_argument(area, process, &shift, OCT01);
		if (IS_REG(PPC(shift)))
		{
			PREG(PPC(shift)) = result;
			CARRY = ((result == 0) ? true : false);
		}
	}
	PC = SHIFT(2 + shift_size(PPC(1), 3, 4));
}

void		or_op(t_area *area, t_process *process) // dir_size = 4ca
{
	uint32_t	shift;
	int32_t		result;

	shift = 2;
	if (RDI_T(OCT00) && RDI_T(OCT01) && R_T(OCT02))
	{
		result = get_argument(area, process, &shift, OCT00);
		result |= get_argument(area, process, &shift, OCT01);
		if (IS_REG(PPC(shift)))
		{
			PREG(PPC(shift)) = result;
			CARRY = ((result == 0) ? true : false);
		}
	}
	PC = SHIFT(2 + shift_size(PPC(1), 3, 4));
}

void		xor_op(t_area *area, t_process *process) // dir_size = 4ca
{
	uint32_t	shift;
	int32_t		result;

	shift = 2;
	if (RDI_T(OCT00) && RDI_T(OCT01) && R_T(OCT02))
	{
		result = get_argument(area, process, &shift, OCT00);
		result ^= get_argument(area, process, &shift, OCT01);
		if (IS_REG(PPC(shift)))
		{
			PREG(PPC(shift)) = result;
			CARRY = ((result == 0) ? true : false);
		}
	}
	PC = SHIFT(2 + shift_size(PPC(1), 3, 4));
}

void		zjmp_op(t_area *area, t_process *process) // dir_size = 2
{
	if (DEBUG_OPS_)
	{
		printf("reg: %p, pc: %u, dir: %d, jump: %d,",
										&PPC(0),
										PC,
										get16(area, process, 1),
										ISHIFT(get16(area, process, 1)));
	}
	if (CARRY == true)
		PC = ISHIFT(((int32_t)get16(area, process, 1)));
	else
		PC = SHIFT(4);
}