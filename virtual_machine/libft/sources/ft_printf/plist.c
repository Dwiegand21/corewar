/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 18:07:05 by lbradama          #+#    #+#             */
/*   Updated: 2019/02/24 14:40:17 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_local.h"

char	*get_real_flags(t_plist *cur)
{
	if (cur->flags.plus == 1 && cur->flags.space == 1)
		cur->flags.space = 0;
	if (cur->precision >= 0 && char_in_string(cur->type, "biduoxpOX"))
		cur->flags.zero = 0;
	if (cur->type == 'p')
		cur->flags.sharp = 1;
	if (cur->type == 'u')
	{
		cur->flags.plus = 0;
		cur->flags.space = 0;
	}
	return (0);
}

int		prepare_plist(t_env *env)
{
	int r;

	env->cur = env->plist;
	while (env->cur)
	{
		get_args(env);
		get_real_flags(env->cur);
		r = 1;
		if (!(env->cur->original))
		{
			if (char_in_string(env->cur->type, ITYPES))
				r = int_processing(env);
			if (char_in_string(env->cur->type, FTYPES))
				r = dbl_processing(env);
			if (env->cur->type == 's' || env->cur->type == 'S')
				r = str_processing(env);
		}
		env->cur = env->cur->next;
		if (!r)
			return (0);
	}
	return (1);
}

int		format_analysis_expression(t_env *env, char *format)
{
	int i;

	i = 0;
	i = is_color(format, env->cur);
	if (i)
		return (i);
	i += is_type_pos(&(format[i]), env);
	while (is_flag(format[i], env->cur))
		i++;
	i += is_width(&(format[i]), env);
	i += is_precision(&(format[i]), env);
	i += is_modifier(&(format[i]), env->cur);
	i += is_type(format[i], env);
	return (i);
}

void	format_analysis_helper(t_env *env, char *format, int i, int type)
{
	if (type == 1)
	{
		env->cur->next = create_plist_node();
		env->cur = env->cur->next;
	}
	else if (type == 2)
	{
		if (i)
		{
			env->cur->original = format;
			env->cur->original_width = i;
		}
	}
}

void	format_analysis(t_env *env, char *format)
{
	int i;

	env->cur = env->plist;
	i = -1;
	while (format[++i])
	{
		if (format[i] != '%')
			continue;
		else
		{
			if (i)
			{
				env->cur->original = format;
				env->cur->original_width = i;
				format_analysis_helper(env, format, i, 1);
			}
			format = format + i + 1;
			i = format_analysis_expression(env, format);
			format = format + i;
			i = -1;
			if (format[i + 1] != 0)
				format_analysis_helper(env, format, i, 1);
		}
	}
	format_analysis_helper(env, format, i, 2);
}
