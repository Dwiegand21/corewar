/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_operations4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 10:51:10 by axtazy            #+#    #+#             */
/*   Updated: 2019/06/13 19:39:17 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void		lfork_op(t_area *area, t_process **carr) // dir_size = 2
{
	int32_t		result;
	t_process	*process;
	int process_id;
	t_process backup;

	process = *carr;
	process_id = process->ordinal_number;
	backup = *process;

	result = get16(area, process, 1);
	new_process(area, &backup, result);

	process = area->carriages->data + process_id;

	PC = SHIFT(3);
	process->f = get_op;
	process->sleep = 1;
	*carr = process;
}

void		aff_op(t_area *area, t_process **carr) // dir_size = 4a
{
	t_process	*process;

	process = *carr;
//	if (IS_REG(PPC(1)))
//	{
//		ft_putchar(PREG(PPC(1))); // ???
//	}
	PC = SHIFT(2 + shift_size(PPC(1), 1, 4));
	process->f = get_op;
	process->sleep = 1;
}