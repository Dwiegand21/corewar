/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_operations1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 10:49:37 by axtazy            #+#    #+#             */
/*   Updated: 2019/07/03 20:21:48 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void		get_op(t_area *area, t_process **carr)
{
	t_process * const	process = *carr;
	const unsigned char	byte = area->map[process->pc];

	if (byte > 0 && byte < 17)
	{
		process->f = g_ops[byte].f;
		process->sleep = g_ops[byte].sleep;
	}
	else
	{
		process->f = g_ops[0].f;
		process->sleep = g_ops[0].sleep;
	}
}

void		next_op(t_area *area, t_process **carr) // dir_size = 4
{
	t_process	*process;

	process = *carr;

	PC = SHIFT(1);
	process->f = get_op;
	process->sleep = 1;
	++area->champs_cmd_total[process->player];
}

void		live_op(t_area *area, t_process **carr) // dir_size = 4
{
	int32_t		value;
	t_process	*process;

	process = *carr;
//	LIVE_S = true;
	process->n_lives = area->n_die_cycle + 1;
	value = -get32(area, process, 1) - 1;
	if (value >= 0 && value < SN_PLAYERS)
	{
		area->players[value].last_live = SN_CYCLES;
		area->win = value;
	}
	bool debug = area->map_owners[process->pc] == process->player;
	area->champs_cmd_awared[process->player] +=
			area->map_owners[process->pc] == process->player;
	SLIVES_IN_ROUND++;
	PC = SHIFT(5);
	process->f = get_op;
	process->sleep = 1;
	++area->champs_cmd_total[process->player];
}

void		ld_op(t_area *area, t_process **carr) // dir_size = 4ca
{
	uint32_t	shift;
	int32_t 	result;
	t_process	*process;

	process = *carr;

	shift = 2;
	if (DI_T(OCT00) && R_T(OCT01))
	{
		result = get_argument(area, process, &shift, OCT00);
//		if (I_T(OCT00))
//			result %= IDX_MOD;
		if (IS_REG(PPC(shift)))
		{
			PREG(PPC(shift)) = result;
			CARRY = ((result == 0) ? true : false);
			area->champs_cmd_awared[process->player] +=
					area->map_owners[process->pc] == process->player;
		}
	}
	PC = SHIFT(2 + shift_size(PPC(1), 2, 4));
	process->f = get_op;
	process->sleep = 1;
	++area->champs_cmd_total[process->player];
}

void		st_op(t_area *area, t_process **carr) // dir_size = 4a
{
	uint32_t	shift;
	t_process	*process;

	process = *carr;

	shift = shift_size(PPC(1), 2, 4);
	if (R_T(OCT00) && RI_T(OCT01)
	&& check_registers(area, process, 2, 4))
	{
		if (IS_REG(PPC(2)))
		{
			area->champs_cmd_awared[process->player] +=
					area->map_owners[process->pc] == process->player;
			if (R_T(OCT01) && IS_REG(PPC(3)))
			{
				PREG(PPC(3)) = PREG(PPC(2));
			}
			else
			{
				set32(area, process,
					get16(area, process, 3) % IDX_MOD, PREG(PPC(2)));
			}
		}
	}
	PC = SHIFT(2 + shift);
	process->f = get_op;
	process->sleep = 1;
	++area->champs_cmd_total[process->player];
}

void		add_op(t_area *area, t_process **carr) // dir_size = 4ca
{
	t_process	*process;

	process = *carr;
	if (R_T(OCT00) && R_T(OCT01) && R_T(OCT02))
	{
		if (IS_REG(PPC(2)) && IS_REG(PPC(3)) && IS_REG(PPC(4)))
		{
			PREG(PPC(4)) = PREG(PPC(2)) + PREG(PPC(3));
			CARRY = (PREG(PPC(4)) == 0) ? true : false;
			area->champs_cmd_awared[process->player] +=
					area->map_owners[process->pc] == process->player;
		}
	}
	PC = SHIFT(2 + shift_size(PPC(1), 3, 4));
	process->f = get_op;
	process->sleep = 1;
	++area->champs_cmd_total[process->player];
}