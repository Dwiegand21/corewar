/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldbl_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 17:03:12 by lbradama          #+#    #+#             */
/*   Updated: 2019/02/24 18:46:19 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_local.h"

void		round_findrank(t_dblinfo *dbl, int32_t elem, int32_t pos)
{
	int32_t		i;
	uint64_t	value;

	i = 0;
	value = dbl->fpart[elem];
	while (++i < pos)
		value /= 10;
	value %= 10;
	if (value > 5)
		round_ldbd_more(dbl, elem, pos);
	else if (value == 5)
		round_ldbd_equal(dbl, elem, pos);
}

int32_t		round_ldbd(t_dblinfo *dbl, int32_t precision)
{
	int32_t		elem;
	int32_t		pos;
	int32_t		first;
	int32_t		full;

	first = nbrlen_healper(dbl->fpart[dbl->flen - 1]);
	full = first - 1 + (dbl->flen - 1) * 17;
	if (precision > full)
		return (full - precision);
	if (precision < first - 1)
	{
		elem = dbl->flen - 1;
		pos = first - precision - 1;
	}
	else
	{
		elem = dbl->flen - 2 - (precision - first) / 17;
		pos = 16 - (precision - first) % 17;
	}
	round_findrank(dbl, elem, pos);
	return (0);
}

void		set_nbr(char **array, uint64_t nbr, int32_t range)
{
	while (range--)
	{
		*(*(array)) = '0' + nbr % 10;
		(*array) -= 1;
		nbr /= 10;
	}
}

void		get_float_prepared_helper(t_dblinfo *dbl,
				int32_t *pec, char **prepared)
{
	int32_t		i;
	int32_t		ffirst;
	int32_t		range;
	uint64_t	fp;

	ffirst = nbrlen_healper(dbl->fpart[dbl->flen - 1]) - 1;
	while (*pec > ffirst + (dbl->flen - 1) * 17)
	{
		**prepared = '0';
		(*prepared)--;
		*pec -= 1;
	}
	i = *pec <= ffirst ? dbl->flen - 1 :
			dbl->flen - 2 - (*pec - 1 - ffirst) / 17;
	if (*pec > ffirst)
	{
		range = (*pec - ffirst) % 17;
		range = range ? range : 17;
		set_nbr(prepared, dbl->fpart[i] / minipowu(10, 17 - range), range);
		i++;
	}
	while (i < dbl->flen - 1)
		set_nbr(prepared, dbl->fpart[i++], 17);
	fp = *pec > ffirst ? ffirst : *pec;
	set_nbr(prepared, dbl->fpart[i] / minipowu(10, ffirst - fp), fp);
}

char		*get_float_prepared(t_dblinfo *dbl, int32_t pec, int32_t sign)
{
	int32_t		i;
	int32_t		len;
	char		*prepared;
	int32_t		ifirst;

	i = -1;
	ifirst = nbrlen_healper(dbl->ipart[dbl->ilen - 1]);
	len = 1 + pec + ifirst + (dbl->ilen - 1) * 17 - !pec + (sign != 0);
	if (!(prepared = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	prepared[len] = 0;
	*prepared = sign ? sign : *prepared;
	prepared += len - 1;
	if (!dbl->flen)
		while (++i < pec)
			*prepared-- = '0';
	else
		get_float_prepared_helper(dbl, &pec, &prepared);
	if (pec)
		*prepared-- = '.';
	i = 0;
	while (i < dbl->ilen - 1)
		set_nbr(&prepared, dbl->ipart[i++], 17);
	set_nbr(&prepared, dbl->ipart[i], ifirst);
	return (prepared + (!sign));
}
