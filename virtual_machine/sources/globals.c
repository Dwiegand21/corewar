/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 12:12:31 by axtazy            #+#    #+#             */
/*   Updated: 2019/06/05 15:52:55 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

t_ops    g_ops[17] =
{
	{ "next",	1,		&next_op },
	{ "live",	10,		&live_op },
	{ "ld",		5,		&ld_op },
	{ "st",		5,		&st_op },
	{ "add",	10,		&add_op },
	{ "sub",	10,		&sub_op },
	{ "and",	6,		&and_op },
	{ "or",		6,		&or_op },
	{ "xor",	6,		&xor_op },
	{ "zjmp",	20,		&zjmp_op },
	{ "ldi",	25,		&ldi_op },
	{ "sti",	25,		&sti_op },
	{ "fork",	800,	&fork_op },
	{ "lld",	10,		&lld_op },
	{ "lldi",	50,		&lldi_op },
	{ "lfork",	1000,	&lfork_op },
	{ "aff",	2,		&aff_op },
};