/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_operations3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 10:50:49 by axtazy            #+#    #+#             */
/*   Updated: 2019/05/30 10:50:49 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void		ldi_op(t_area *area, t_process *process)
{
	int32_t		shift;

	shift = 3
			+ ((D_T(OCT00(PPC(1))) ? 4 : 1) + (I_T(OCT00(PPC(1)))))
			+ (D_T(OCT01(PPC(1))) ? 4 : 2);
	if (RDI_T(OCT00(PPC(1))) && RD_T(OCT01(PPC(1))) && R_T(OCT02(PPC(1))))
	{
		if (IS_REG(PPC(shift - 1)))
		{
			if (R_T(OCT00(PPC(1))))
			{
				ldi_method1(area, process);
			}
			else if (D_T(OCT00(PPC(1))))
			{
				ldi_method2(area, process);
			}
			else
			{
				ldi_method3(area, process);
			}
		}
	}
	PC = SHIFT(shift);
}

void		sti_op(t_area *area, t_process *process)
{

}

void		fork_op(t_area *area, t_process *process)
{

}

void		lld_op(t_area *area, t_process *process)
{

}

void		lldi_op(t_area *area, t_process *process)
{

}