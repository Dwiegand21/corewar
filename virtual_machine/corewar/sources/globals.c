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

t_ops    g_ops[19] =
{
	{ "next"		,	1		,		&next_op },		// 0
	{ "live"		,	10	 -1,		&live_op },		// 1
	{ "ld"		,	5 -1		,		&ld_op },		// 2
	{ "st"		,	5 -1		,		&st_op },		// 3
	{ "add"		,	10	 -1,		&add_op },		// 4
	{ "sub"		,	10	 -1,		&sub_op },		// 5
	{ "and"		,	6 -1		,		&and_op },		// 6
	{ "or"		,	6 -1		,		&or_op },		// 7
	{ "xor"		,	6 -1		,		&xor_op },		// 8
	{ "zjmp"		,	20	 -1,		&zjmp_op },		// 9
	{ "ldi"		,	25	 -1,		&ldi_op },		// 10
	{ "sti"		,	25	 -1,		&sti_op },		// 11
	{ "fork"		,	800	 -1,		&fork_op },		// 12
	{ "lld"		,	10	 -1,		&lld_op },		// 13
	{ "lldi"		,	50	 -1,		&lldi_op },		// 14
	{ "lfork"		,	1000	 -1,		&lfork_op },	// 15
	{ "aff"		,	2 -1		,		&aff_op },		// 16
	{ "get"		,   1		,		&get_op },		// 17
		{ "dead"		,	2 -1		,		0 }
};

int32_t		g_db_from = 0;