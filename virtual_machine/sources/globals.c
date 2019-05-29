/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 12:12:31 by axtazy            #+#    #+#             */
/*   Updated: 2019/05/29 17:34:00 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

t_ops    op_tab[17] =x
{
	{ "next",	0,		NULL },
	{ "live",	10,		NULL },
	{ "ld",		5,		NULL },
	{ "st",		5,		NULL },
	{ "add",	10,		NULL },
	{ "sub",	10,		NULL },
	{ "and",	6,		NULL },
	{ "or",		6,		NULL },
	{ "xor",	6,		NULL },
	{ "zjmp",	20,		NULL },
	{ "ldi",	25,		NULL },
	{ "sti",	25,		NULL },
	{ "fork",	800,	NULL },
	{ "lld",	10,		NULL },
	{ "lldi",	50,		NULL },
	{ "lfork",	1000,	NULL },
	{ "aff",	2,		NULL },
};