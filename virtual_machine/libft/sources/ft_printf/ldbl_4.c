/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldbl_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 17:03:12 by lbradama          #+#    #+#             */
/*   Updated: 2019/02/26 16:45:41 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_local.h"

int32_t		special_values(t_env *env, t_lld *lld)
{
	int32_t		i;

	i = 0;
	if (lld->blld.fraction << 1)
		env->cur->prepared = ft_strdup("nan");
	else
	{
		if (lld->blld.sign)
			env->cur->prepared = ft_strdup("-inf");
		else
			env->cur->prepared = ft_strdup("inf");
	}
	if (!env->cur->prepared)
		return (0);
	if (env->cur->type == 'F')
	{
		while (env->cur->prepared[i])
		{
			if (env->cur->prepared[i] >= 'a' && env->cur->prepared[i] <= 'z')
				env->cur->prepared[i] -= 32;
			i++;
		}
	}
	env->cur->len = ft_strlen(env->cur->prepared);
	return (1);
}

t_dblinfo	*dblinfo_init(t_bitlld *blld)
{
	t_dblinfo	*dbl;

	dbl = NULL;
	if ((dbl = (t_dblinfo *)malloc(sizeof(t_dblinfo))))
	{
		if (!(dbl->ipart = malloc(sizeof(uint64_t) * 291)))
		{
			free(dbl);
			return (NULL);
		}
		if (!(dbl->fpart = malloc(sizeof(uint64_t) * 984)))
		{
			free(dbl->ipart);
			free(dbl);
			return (NULL);
		}
		ft_memset(dbl->ipart, 0, sizeof(uint64_t) * 291);
		ft_memset(dbl->fpart, 0, sizeof(uint64_t) * 984);
		dbl->order = (blld->order & 0x7FFF) - 0x3FFE;
		dbl->fraction = blld->fraction;
		dbl->ilen = 1;
		dbl->flen = 0;
	}
	return (dbl);
}

int32_t		dblinfo_del(t_dblinfo **dbl, int32_t val)
{
	if (*dbl)
	{
		if ((*dbl)->ipart)
			free((*dbl)->ipart);
		if ((*dbl)->fpart)
			free((*dbl)->fpart);
		free((*dbl));
		(*dbl) = NULL;
	}
	return (val);
}

int32_t		ldbl_process_pre(t_env *env, t_lld lld)
{
	if (lld.blld.sign)
		return ('-');
	else
	{
		if (env->cur->flags.plus)
			return ('+');
		else if (env->cur->flags.space)
			return (' ');
	}
	return (0);
}

int32_t		ldbl_process(t_env *env)
{
	t_lld		lld;
	int32_t		sign;
	t_dblinfo	*dbl;

	dbl = NULL;
	lld.value = env->cur->f;
	if (!(dbl = dblinfo_init(&(lld.blld))))
		return (0);
	if (dbl->order == 16385)
		return ((special_values(env, &lld)));
	if (dbl->order < 64 && (dbl->order < 0 || (dbl->fraction << dbl->order)))
		if (!(calculate_fpart(dbl, dbl->order)))
			return (dblinfo_del(&dbl, 0));
	if (dbl->order > 0 && (dbl->fraction >> (64 - dbl->order)))
		if (!(calculate_ipart(dbl, dbl->order)))
			return (dblinfo_del(&dbl, 0));
	round_ldbd(dbl, env->cur->precision);
	sign = ldbl_process_pre(env, lld);
	if (!(env->cur->prepared =
		get_float_prepared(dbl, env->cur->precision, sign)))
		return (dblinfo_del(&dbl, 0));
	env->cur->len = ft_strlen(env->cur->prepared);
	return (dblinfo_del(&dbl, 1));
}
