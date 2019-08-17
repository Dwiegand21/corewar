/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 12:12:31 by axtazy            #+#    #+#             */
/*   Updated: 2019/06/12 14:52:11 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

t_ops	g_ops[19] =
{
	{ "next", 1, &next_op },
	{ "live", 10 - 1, &live_op },
	{ "ld", 5 - 1, &ld_op },
	{ "st", 5 - 1, &st_op },
	{ "add", 10 - 1, &add_op },
	{ "sub", 10 - 1, &sub_op },
	{ "and", 6 - 1, &and_op },
	{ "or", 6 - 1, &or_op },
	{ "xor", 6 - 1, &xor_op },
	{ "zjmp", 20 - 1, &zjmp_op },
	{ "ldi", 25 - 1, &ldi_op },
	{ "sti", 25 - 1, &sti_op },
	{ "fork", 800 - 1, &fork_op },
	{ "lld", 10 - 1, &lld_op },
	{ "lldi", 50 - 1, &lldi_op },
	{ "lfork", 1000 - 1, &lfork_op },
	{ "aff", 2 - 1, &aff_op },
	{ "get", 1, &get_op },
	{ "dead", 2 - 1, 0 }
};

int32_t			g_db_from = 0;
t_vm_vector_int	*g_buffer = 0;
