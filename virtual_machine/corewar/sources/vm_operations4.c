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

void		lfork_op(t_area *area, t_process *process) // dir_size = 2
{
	int32_t		result;

	result = get16(area, process, 1);
	new_process(area, process, result);
	PC = SHIFT(3);
}

void		aff_op(t_area *area, t_process *process) // dir_size = 4a
{
//	if (IS_REG(PPC(1)))
//	{
//		ft_putchar(PREG(PPC(1))); // ???
//	}
	PC = SHIFT(2 + shift_size(PPC(1), 1, 4));
}