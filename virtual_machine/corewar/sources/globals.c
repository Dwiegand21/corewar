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

t_ops    g_ops[17] =
{
	{ "next"	,	1		,		&next_op },		// 0
	{ "live"	,	10		,		&live_op },		// 1
	{ "ld"		,	5		,		&ld_op },		// 2
	{ "st"		,	5		,		&st_op },		// 3
	{ "add"		,	10		,		&add_op },		// 4
	{ "sub"		,	10		,		&sub_op },		// 5
	{ "and"		,	6		,		&and_op },		// 6
	{ "or"		,	6		,		&or_op },		// 7
	{ "xor"		,	6		,		&xor_op },		// 8
	{ "zjmp"	,	20		,		&zjmp_op },		// 9
	{ "ldi"		,	25		,		&ldi_op },		// 10
	{ "sti"		,	25		,		&sti_op },		// 11
	{ "fork"	,	800		,		&fork_op },		// 12
	{ "lld"		,	10		,		&lld_op },		// 13
	{ "lldi"	,	50		,		&lldi_op },		// 14
	{ "lfork"	,	1000	,		&lfork_op },	// 15
	{ "aff"		,	2		,		&aff_op },		// 16
};

int32_t		g_db_from = 0;