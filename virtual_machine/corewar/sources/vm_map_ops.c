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
	return ((((int32_t)(PPC(shift))) << 24)
			| (((int32_t)(PPC(shift + 1))) << 16)
			| (((int32_t)(PPC(shift + 2))) << 8)
			| (((int32_t)(PPC(shift + 3)))));
}

int16_t		get16(t_area *area, t_process *process, uint32_t shift)
{
	return ((((int16_t)(PPC(shift))) << 8)
			| (((int16_t)(PPC(shift + 1))) << 0));
}

static inline int get_price_by_player(int whose_byte, int player)
{
	if (whose_byte == player)
		return (0);
	else if (whose_byte == -1)
		return (1);
	else
		return (2);
}

void set32(t_area *area, t_process *process, uint32_t shift, int32_t value,
		   int whose)
{
	uint8_t *const map_owners = area->map_owners;

	area->champs_agro[whose] +=
		get_price_by_player(map_owners[(PC + shift) % MEM_SIZE], whose) +
		get_price_by_player(map_owners[(PC + shift + 1) % MEM_SIZE], whose) +
		get_price_by_player(map_owners[(PC + shift + 2) % MEM_SIZE], whose) +
		get_price_by_player(map_owners[(PC + shift + 3) % MEM_SIZE], whose);

	map_owners[(PC + shift) % MEM_SIZE] = 	whose;
	map_owners[(PC + shift + 1) % MEM_SIZE] = whose;
	map_owners[(PC + shift + 2) % MEM_SIZE] = whose;
	map_owners[(PC + shift + 3) % MEM_SIZE] = whose;

	PPC(shift) = (uint8_t)((value >> 24) & 0xFF);
	PPC(shift + 1) = (uint8_t)((value >> 16) & 0xFF);
	PPC(shift + 2) = (uint8_t)((value >> 8) & 0xFF);
	PPC(shift + 3) = (uint8_t)((value >> 0) & 0xFF);
}

void		set16(t_area *area,
							t_process *process,
							uint32_t shift,
							int16_t value)
{
	PPC(shift) = (uint8_t)(value & 0xFF);
	PPC(shift + 1) = (uint8_t)((value >> 8) & 0xFF);
}