/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 19:12:18 by lbradama          #+#    #+#             */
/*   Updated: 2019/02/22 20:57:11 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_local.h"

int		is_arg_pos(char *str, int *res)
{
	int i;
	int r;

	i = 0;
	r = 0;
	i = read_int_to_param(str, &r, 0);
	if (str[i] == '$')
	{
		*res = r;
		return (i + 1);
	}
	return (0);
}

int		is_type_pos(char *c, t_env *env)
{
	int i;

	i = 0;
	if (env->dollar)
	{
		i += is_arg_pos(&(c[i]), &(env->cur->type_pos));
		env->args->arg_list[env->cur->type_pos].type[2] = 'i';
	}
	return (i);
}

int		is_width(char *c, t_env *env)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (c[i] != '*')
	{
		while (c[i + j] >= '0' && c[i + j] <= '9')
			j++;
		if (c[i + j] != '*')
			return (read_int_to_param(c, &env->cur->width, 0));
		i += j;
	}
	i++;
	i += is_arg_pos(&(c[i]), &env->cur->width_pos);
	if (env->dollar)
		env->args->arg_list[env->cur->width_pos].type[2] = 'i';
	else
	{
		env->cur->width_pos = env->args->cur;
		env->args->arg_list[env->args->cur].type[2] = 'i';
		env->args->cur = env->args->cur + 1;
	}
	return (i);
}

void	is_precision_helper(t_env *env)
{
	if (env->dollar)
		env->args->arg_list[env->cur->precision_pos].type[2] = 'i';
	else
	{
		env->cur->precision_pos = env->args->cur;
		env->args->arg_list[env->args->cur].type[2] = 'i';
		env->args->cur = env->args->cur + 1;
	}
}

int		is_precision(char *c, t_env *env)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (c[i] == '.')
	{
		i++;
		env->cur->precision = 0;
		if (c[i] != '*')
		{
			while (c[i + j] >= '0' && c[i + j] <= '9')
				j++;
			if (c[i + j] != '*')
				return (read_int_to_param(&(c[i]), &env->cur->precision, 1));
			i += j;
		}
		i++;
		i += is_arg_pos(&(c[i]), &env->cur->precision_pos);
		is_precision_helper(env);
		return (i);
	}
	return (0);
}
