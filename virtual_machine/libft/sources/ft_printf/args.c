/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 18:00:31 by lbradama          #+#    #+#             */
/*   Updated: 2019/02/22 18:53:21 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_local.h"

void	get_args(t_env *env)
{
	if (env->cur->type_pos >= 0)
	{
		if (env->cur->width_pos >= 0)
		{
			env->cur->width = env->args->arg_list[env->cur->width_pos].i;
			if (env->cur->width < 0)
			{
				env->cur->flags.minus = 1;
				env->cur->width *= -1;
			}
		}
		if (env->cur->precision_pos >= 0)
			env->cur->precision =
			env->args->arg_list[env->cur->precision_pos].i;
		env->cur->i = env->args->arg_list[env->cur->type_pos].i;
		env->cur->f = env->args->arg_list[env->cur->type_pos].f;
		env->cur->s = env->args->arg_list[env->cur->type_pos].s;
		env->cur->ws = env->args->arg_list[env->cur->type_pos].ws;
	}
}

int		arg_cmp(t_pargs *args, int arg_pos, char *mod, char *type)
{
	if (mod && mod[0])
	{
		if (args->arg_list[arg_pos].type[0] != mod[0] ||
			args->arg_list[arg_pos].type[1] != mod[1])
			return (0);
	}
	else
	{
		if (args->arg_list[arg_pos].type[0] != 0)
			return (0);
		if (!char_in_string(args->arg_list[arg_pos].type[2], type))
			return (0);
	}
	if (type && type[0])
	{
		if (!char_in_string(args->arg_list[arg_pos].type[2], type))
			return (0);
	}
	else
	{
		if (args->arg_list[arg_pos].type[2] != 0)
			return (0);
	}
	return (1);
}

int		get_args_count(t_env *env, char *format)
{
	int shift;

	shift = 0;
	while (*format)
	{
		if (*format != '%')
			format++;
		else
		{
			format++;
			if ((shift = check_valid_format(format, env)) < 0)
				return (-1);
			format += shift;
		}
	}
	if (env->max_arg_pos > env->max_arg_count)
		return (-1);
	if (env->max_arg_pos && env->max_arg_pos < env->max_arg_count)
		return (env->max_arg_pos);
	return (env->max_arg_count);
}
