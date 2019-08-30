/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldbl_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 17:03:12 by lbradama          #+#    #+#             */
/*   Updated: 2019/02/26 16:48:42 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_local.h"

int32_t		calculate_fpart(t_dblinfo *dbl, int16_t order)
{
	uint64_t	*tpart;
	int32_t		tcur;
	int32_t		i;

	dbl->flen = 1;
	if (!(tpart = malloc(sizeof(uint64_t) * 984)))
		return (0);
	tpart[0] = 1;
	dbl->fpart[0] = 1;
	tcur = 1;
	while (order < 64 && (order < 0 || (dbl->fraction << order)))
	{
		powup(tpart, tcur, 5);
		i = -1;
		if (order < 0 || (dbl->fraction << order))
			while (++i < dbl->flen)
				dbl->fpart[i] *= 10;
		if (order > -1 && ((dbl->fraction << order) & 0x8000000000000000ULL))
			fold_lists(dbl->fpart, tpart, tcur);
		mod_step(dbl->fpart, &dbl->flen);
		mod_step(tpart, &tcur);
		order++;
	}
	free(tpart);
	return (1);
}

int32_t		calculate_ipart(t_dblinfo *dbl, int16_t order)
{
	uint64_t	*tpart;
	int32_t		tcur;

	if (!(tpart = malloc(sizeof(uint64_t) * 291)))
		return (0);
	tpart[0] = 1;
	dbl->ipart[0] = 0;
	tcur = 1;
	while (order > 0 && (order > 64 || (dbl->fraction >> (64 - order))))
	{
		mod_step(dbl->ipart, &dbl->ilen);
		mod_step(tpart, &tcur);
		if (order < 65 && ((dbl->fraction >> (64 - order)) & 0x01))
		{
			fold_lists(dbl->ipart, tpart, tcur);
			dbl->ilen = tcur;
		}
		powup(tpart, tcur, 2);
		order--;
	}
	mod_step(dbl->ipart, &dbl->ilen);
	free(tpart);
	return (1);
}

void		round_ldbd_more_healper(t_dblinfo *dbl, int32_t mod)
{
	int32_t		i;

	i = 0;
	while ((i < dbl->ilen) && (dbl->ipart[i] / 100000000000000000ULL))
	{
		mod = dbl->ipart[i] / 100000000000000000ULL;
		dbl->ipart[i] %= 100000000000000000ULL;
		i++;
		if (i < dbl->ilen)
			dbl->ipart[i] += mod;
		else
		{
			dbl->ipart[i] += mod;
			dbl->ilen++;
			break ;
		}
	}
}

void		round_ldbd_more(t_dblinfo *dbl, int32_t elem, int32_t pos)
{
	int32_t		mod;
	int32_t		ffirst;

	mod = 0;
	ffirst = nbrlen_healper(dbl->fpart[dbl->flen - 1]) - 1;
	dbl->fpart[elem] += minipowu(10, pos);
	while ((elem < dbl->flen - 1) && (dbl->fpart[elem] / 100000000000000000ULL))
	{
		mod = dbl->fpart[elem] / 100000000000000000ULL;
		dbl->fpart[elem] %= 100000000000000000ULL;
		elem++;
		if (elem < dbl->flen)
			dbl->fpart[elem] += mod;
	}
	if (dbl->fpart[elem] / minipowu(10, ffirst) == 2)
	{
		dbl->ipart[0] += 1;
		round_ldbd_more_healper(dbl, mod);
	}
}

void		round_ldbd_equal(t_dblinfo *dbl, int32_t elem, int32_t pos)
{
	int32_t		state;
	int32_t		cur;
	uint64_t	ffirst;
	uint64_t	pwl;
	uint64_t	tmp;

	cur = elem;
	pwl = minipowu(10, pos);
	tmp = dbl->fpart[elem] % pwl;
	state = pos > 1 && tmp > 0 ? 1 : 0;
	if (!(pos > 1 && tmp > 0) && ++cur)
		while (!state && cur < dbl->flen)
			if (dbl->fpart[cur] > 0)
				state = 1;
	if (state)
		round_ldbd_more(dbl, elem, pos);
	else
	{
		ffirst = nbrlen_healper(dbl->fpart[dbl->flen - 1]) - 1;
		if (ffirst == (uint64_t)pos && dbl->ipart[0] % 2)
			round_ldbd_more(dbl, elem, pos);
		else if (ffirst != (uint64_t)pos && (dbl->fpart[elem] / pwl) % 2)
			round_ldbd_more(dbl, elem, pos);
	}
}
