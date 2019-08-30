/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 18:37:11 by lbradama          #+#    #+#             */
/*   Updated: 2019/02/26 17:03:59 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_local.h"

int		str_processing(t_env *env)
{
	if (env->cur->type == 'S' ||
		(env->cur->type == 's' && env->cur->mod[0] == 'l'))
	{
		if (!lstr_tramsformation(env, env->cur->ws))
			return (0);
		if (!post_str(env))
			return (0);
	}
	else
	{
		if (!str_transformation(env->cur, env->cur->s))
			return (0);
		if (!post_str(env))
			return (0);
	}
	return (1);
}

void	int_processing_helper(t_env *env)
{
	if (env->cur->mod[0] == 'h')
	{
		if (env->cur->mod[1] == 'h')
		{
			if (char_in_string(env->cur->type, "id"))
				env->cur->i = (char)env->cur->i;
			else if (char_in_string(env->cur->type, "ubxXo"))
				env->cur->i = (unsigned char)env->cur->i;
		}
		else
		{
			if (char_in_string(env->cur->type, "id"))
				env->cur->i = (short int)env->cur->i;
			else if (char_in_string(env->cur->type, "ubxXo"))
				env->cur->i = (short unsigned int)env->cur->i;
		}
	}
}

int		int_processing(t_env *env)
{
	int_processing_helper(env);
	if (char_in_string(env->cur->type, "cC%"))
	{
		if (!pre_char(env) || !post_char(env))
			return (0);
	}
	else if (char_in_string(env->cur->type, "idDuU"))
	{
		if (!pre_int(env) || !post_int(env))
			return (0);
	}
	else if (char_in_string(env->cur->type, "xXoOp"))
	{
		if (!pre_hex(env) || !post_hex(env))
			return (0);
	}
	else if (env->cur->type == 'b')
	{
		if (!pre_bin(env) || !post_bin(env))
			return (0);
	}
	return (1);
}

int		dbl_processing_helper(t_env *env)
{
	int		i;
	int		flag;
	char	*tmp;

	i = -1;
	flag = 1;
	while (flag && env->cur->prepared[++i])
		if ((env->cur->prepared[i] >= 'a' && env->cur->prepared[i] <= 'z') ||
			(env->cur->prepared[i] >= 'A' && env->cur->prepared[i] <= 'Z') ||
			env->cur->prepared[i] == '.')
			flag = 0;
	if (flag)
	{
		if (!(tmp = (char *)malloc(env->cur->len + 2)))
			return (0);
		tmp[env->cur->len + 1] = 0;
		tmp[env->cur->len] = '.';
		i = -1;
		while (env->cur->prepared[++i])
			tmp[i] = env->cur->prepared[i];
		change_prepared(env, &tmp, -1);
	}
	return (1);
}

int		dbl_processing(t_env *env)
{
	if (env->cur->precision == -1)
		env->cur->precision = 6;
	if (env->cur->type == 'f' || env->cur->type == 'F')
	{
		if (!ldbl_process(env))
			return (0);
		if (env->cur->flags.sharp)
			if (!dbl_processing_helper(env))
				return (0);
		if (!post_float(env))
			return (0);
	}
	return (1);
}
