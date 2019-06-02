/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_opeartions2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 10:50:20 by axtazy            #+#    #+#             */
/*   Updated: 2019/05/30 10:50:20 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void		sub_op(t_area *area, t_process *process)
{
	if (R_T(OCT00(PPC(1))) && R_T(OCT01(PPC(1))) && R_T(OCT02(PPC(1))))
	{
		if (IS_REG(PPC(2)) && IS_REG(PPC(6)) && IS_REG(PPC(10)))
		{
			PREG[PPC(10) - 1] = PREG[PPC(2) - 1] - PREG[PPC(6) - 1];
			CARRY = (PREG[PPC(10) - 1] == 0);
		}
	}
	PC = SHIFT(14);
}

void		and_op(t_area *area, t_process *process)
{
	int32_t		shift;

	shift = 3
			+ ((D_T(OCT00(PPC(1))) ? 4 : 1) + I_T(OCT00(PPC(1))))
			+ ((D_T(OCT01(PPC(1))) ? 4 : 1) + I_T(OCT01(PPC(1))));
	if (RDI_T(OCT00(PPC(1))) && RDI_T(OCT01(PPC(1))) && R_T(OCT02(PPC(1))))
	{
		if (IS_REG(PPC(shift - 1)))
		{
			if (R_T(OCT00(PPC(1))))
			{
				and_method1(area, process);
			}
			else if (D_T(OCT00(PPC(1))))
			{
				and_method2(area, process);
			}
			else
			{
				and_method3(area, process);
			}
			CARRY = ((PREG[PPC(shift - 1)] == 0) ? 1 : 0);
		}
	}
	PC = SHIFT(shift);
}

void		or_op(t_area *area, t_process *process)
{
	int32_t		shift;

	shift = 3
			+ ((D_T(OCT00(PPC(1))) ? 4 : 1) + I_T(OCT00(PPC(1))))
			+ ((D_T(OCT01(PPC(1))) ? 4 : 1) + I_T(OCT01(PPC(1))));
	if (RDI_T(OCT00(PPC(1))) && RDI_T(OCT01(PPC(1))) && R_T(OCT02(PPC(1))))
	{
		if (IS_REG(PPC(shift - 1)))
		{
			if (R_T(OCT00(PPC(1))))
			{
				or_method1(area, process);
			}
			else if (D_T(OCT00(PPC(1))))
			{
				or_method2(area, process);
			}
			else
			{
				or_method3(area, process);
			}
			CARRY = ((PREG[PPC(shift - 1)] == 0) ? 1 : 0);
		}
	}
	PC = SHIFT(shift);
}

void		xor_op(t_area *area, t_process *process)
{
	int32_t		shift;

	shift = 3
			+ ((D_T(OCT00(PPC(1))) ? 4 : 1) + I_T(OCT00(PPC(1))))
			+ ((D_T(OCT01(PPC(1))) ? 4 : 1) + I_T(OCT01(PPC(1))));
	if (RDI_T(OCT00(PPC(1))) && RDI_T(OCT01(PPC(1))) && R_T(OCT02(PPC(1))))
	{
		if (IS_REG(PPC(shift - 1)))
		{
			if (R_T(OCT00(PPC(1))))
			{
				xor_method1(area, process);
			}
			else if (D_T(OCT00(PPC(1))))
			{
				xor_method2(area, process);
			}
			else
			{
				xor_method3(area, process);
			}
			CARRY = ((PREG[PPC(shift - 1)] == 0) ? 1 : 0);
		}
	}
	PC = SHIFT(shift);
}

void		zjmp_op(t_area *area, t_process *process)
{
	if (CARRY)
		PC = ISHIFT(be_get16(&PPC(1)));
	else
		PC = SHIFT(3);
}