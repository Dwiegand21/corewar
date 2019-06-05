/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 06:03:44 by axtazy            #+#    #+#             */
/*   Updated: 2019/06/05 11:32:59 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int32_t		get32(t_area *area, t_process *process, uint32_t shift)
{
	return ((((int32_t)(PPC(shift))) << 0)
			| (((int32_t)(PPC(shift + 1))) << 8)
			| (((int32_t)(PPC(shift + 2))) << 16)
			| (((int32_t)(PPC(shift + 3))) << 24));
}

int16_t		get16(t_area *area, t_process *process, uint32_t shift)
{
	return ((((int16_t)(PPC(shift))) << 0)
			| (((int16_t)(PPC(shift + 1))) << 8));
}

void		set32(t_area *area,
							t_process *process,
							uint32_t shift,
							int32_t value)
{
	PPC(shift) = (uint8_t)(value & 0xFF);
	PPC(shift + 1) = (uint8_t)((value >> 8) & 0xFF);
	PPC(shift + 2) = (uint8_t)((value >> 16) & 0xFF);
	PPC(shift + 3) = (uint8_t)((value >> 24) & 0xFF);
}

void		set16(t_area *area,
							t_process *process,
							uint32_t shift,
							int16_t value)
{
	PPC(shift) = (uint8_t)(value & 0xFF);
	PPC(shift + 1) = (uint8_t)((value >> 8) & 0xFF);
}