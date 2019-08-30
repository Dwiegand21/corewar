/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocessing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 19:35:24 by lbradama          #+#    #+#             */
/*   Updated: 2019/02/24 14:55:20 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_local.h"

int		pre_char(t_env *env)
{
	if (env->cur->type == 'C' ||
		(env->cur->type == 'c' && env->cur->mod[0] == 'l'))
	{
		if (!wchar_transformation(env, (uint32_t)env->cur->i))
			return (0);
	}
	else
	{
		if (!(env->cur->prepared = malloc(sizeof(char) * 1 + env->cur->i != 0)))
			return (0);
		if (env->cur->i == 0 && env->cur->type == '%')
			env->cur->prepared[0] = 0;
		else
		{
			env->cur->prepared[0] = env->cur->i;
			env->cur->prepared[1] = 0;
		}
		env->cur->len = env->cur->i == 0 && env->cur->type == '%' ? 0 : 1;
	}
	return (1);
}

int		pre_int(t_env *env)
{
	unsigned long long int	nbr;
	int						sign;

	sign = 0;
	if (env->cur->type == 'u' || env->cur->type == 'U')
		nbr = env->cur->i;
	else
	{
		if (env->cur->i < 0)
		{
			sign = '-';
			nbr = -env->cur->i;
		}
		else
		{
			if (env->cur->flags.plus)
				sign = '+';
			else if (env->cur->flags.space)
				sign = ' ';
			nbr = env->cur->i;
		}
	}
	return (llitoa(env->cur, nbr, sign));
}

int		pre_hex(t_env *env)
{
	int type;

	if (env->cur->precision == 0 && env->cur->i == 0)
	{
		if (!(env->cur->prepared = malloc(sizeof(char) * 1)))
			return (0);
		env->cur->len = 0;
		env->cur->prepared[0] = 0;
		return (1);
	}
	type = env->cur->type == 'O' || env->cur->type == 'X' ? 1 : 0;
	if (env->cur->type == 'o' || env->cur->type == 'O')
		return (octal_base(env, (uint64_t)env->cur->i));
	else
		return (hex_base(env, (uint64_t)env->cur->i, type));
}

int		pre_bin(t_env *env)
{
	unsigned long long	number;
	unsigned int		size;

	size = sizeof(int);
	if (env->cur->mod[0] == 'l')
	{
		size = sizeof(long);
		if (env->cur->mod[1] == 'l')
			size = sizeof(long long);
	}
	else if (env->cur->mod[0] == 'h')
	{
		size = sizeof(short);
		if (env->cur->mod[1] == 'h')
			size = sizeof(char);
	}
	else if (env->cur->mod[0] == 'z')
		size = sizeof(size_t);
	else if (env->cur->mod[0] == 'j')
		size = sizeof(uintmax_t);
	number = env->cur->i;
	if (env->cur->flags.sharp)
		return (dectobin_sharp(env->cur, number, size));
	else
		return (dectobin(env->cur, number, size));
}
