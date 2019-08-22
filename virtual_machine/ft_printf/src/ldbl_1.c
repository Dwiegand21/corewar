/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldbl_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 17:03:12 by lbradama          #+#    #+#             */
/*   Updated: 2019/02/24 18:45:09 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

uint64_t	minipowu(int32_t nbr, int32_t power)
{
	uint64_t	res;

	res = 1;
	while (power--)
		res *= nbr;
	return (res);
}

void		fold_lists(uint64_t *fpart, uint64_t *tpart, int32_t tcur)
{
	int32_t		i;

	i = -1;
	while (++i < tcur)
		fpart[i] += tpart[i];
}

void		powup(uint64_t *tpart, int32_t tcur, int32_t power)
{
	int32_t		i;

	i = -1;
	while (++i < tcur)
		tpart[i] *= power;
}

void		mod_step(uint64_t *part, int32_t *n)
{
	int32_t		i;
	int32_t		mod;

	mod = 0;
	i = -1;
	while (++i < *n)
	{
		part[i] += mod;
		mod = 0;
		mod = part[i] / 100000000000000000ULL;
		part[i] %= 100000000000000000ULL;
	}
	if (mod)
	{
		part[i] = mod;
		*n += 1;
	}
}

uint64_t	nbrlen_healper(uint64_t nbr)
{
	uint64_t	length;

	length = 1;
	while (nbr / 10)
	{
		length++;
		nbr /= 10;
	}
	return (length);
}
