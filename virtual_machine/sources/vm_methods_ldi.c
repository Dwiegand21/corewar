/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_methods_ldi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 22:07:56 by dwiegand          #+#    #+#             */
/*   Updated: 2019/06/02 22:07:56 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int32_t		get_argument(t_area *area,
							t_process *process,
							int32_t *shift,
							uint8_t type)
{
	if (R_T(type))
	{
		*shift += 1;
		return (PREG[PPC(*shift - 1)]);
	}
	else if (D_T(type))
	{
		*shift += 4;
		return (be_get32(&PPC(*shift - 4)));
	}
	else
	{
		*shift += 2;
		return (be_get32(&PIPC(be_get16(&PPC(*shift - 2)))));
	}
}

void		ldi_method1(t_area *area, t_process *process) // first is REG
{
	int32_t		shift;

	shift = 2 + 1;
	if (R_T(OCT01(PPC(1))) && IS_REG(PPC(3))) // REG
	{
		PREG[PPC(shift + 1)] = PREG[PPC(shift - 1)] & PREG[PPC(shift)];
	}
	else if (D_T(OCT01(PPC(1)))) // DIR
	{
		PREG[PPC(shift + 4)] = PREG[PPC(shift - 1)] & be_get32(&PPC(shift));
	}
	else // IND
	{
		PREG[PPC(shift + 2)] = PREG[PPC(shift - 1)]
				& be_get32(&PIPC(be_get16(&PPC(shift))));
	}
}

void		ldi_method2(t_area *area, t_process *process) // first is DIR
{
	int32_t		shift;

	shift = 2 + 4;
	if (R_T(OCT01(PPC(1))) && IS_REG(PPC(6))) // REG
	{
		PREG[PPC(shift + 1)] = be_get32(&PPC(shift - 4)) & PREG[PPC(shift)];
	}
	else if (D_T(OCT01(PPC(1)))) // DIR
	{
		PREG[PPC(shift + 4)] = be_get32(&PPC(shift - 4))
				& be_get32(&PPC(shift));
	}
	else // IND
	{
		PREG[PPC(shift + 2)] = be_get32((&PPC(shift - 4)))
				& be_get32(&PIPC(be_get16(&PPC(shift))));
	}
}

void		ldi_method3(t_area *area, t_process *process) // first is IND
{
	int32_t		shift;

	shift = 2 + 2;
	if (R_T(OCT01(PPC(1))) && IS_REG(PPC(4)))
	{
		PREG[shift + 1] = be_get32(&PIPC(be_get16(&PPC(shift - 2))))
				& PREG[PPC(shift)];
	}
	else if (D_T(OCT01(PPC(1))))
	{
		PREG[shift + 4] = be_get32(&PIPC(be_get16(&PPC(shift - 2))))
				& be_get32(&PPC(shift));
	}
	else
	{
		PREG[shift + 2] = be_get32(&PIPC(be_get16(&PPC(shift - 2))))
				& be_get32(&PIPC(be_get16(&PPC(shift))));
	}
}
