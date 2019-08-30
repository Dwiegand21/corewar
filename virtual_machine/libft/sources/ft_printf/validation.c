/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 18:52:26 by lbradama          #+#    #+#             */
/*   Updated: 2019/02/26 17:34:30 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_local.h"

int		check_valid_format_helper(char *format, t_env *env, int dollar)
{
	int i;
	int tmp;

	i = 0;
	while (format[i] >= '0' && format[i] <= '9')
		i++;
	if (format[i] == '*')
	{
		i++;
		if (format[i] >= '1' && format[i] <= '9')
		{
			i += shift_int(&(format[i]), &tmp);
			if (format[i] != '$')
				return (-1);
			if (format[i] == '$' && !dollar)
				return (-1);
			if (tmp > env->max_arg_pos)
				env->max_arg_pos = tmp;
			i++;
		}
		else if (dollar)
			return (-1);
		env->max_arg_count += 1;
	}
	return (i);
}

char	*check_valid_format_prehelper(char *format, t_env *env, int *dollar)
{
	int t;

	t = 0;
	if (format[t] >= '1' && format[t] <= '9')
		while (format[t] >= '0' && format[t] <= '9')
			t++;
	if ((*dollar = (format[t] == '$')))
	{
		t = 0;
		format += shift_int(format, &t);
		format++;
		if (t > env->max_arg_pos)
			env->max_arg_pos = t;
	}
	while (char_in_string(*format, FLAGS))
		format++;
	if ((t = check_valid_format_helper(format, env, *dollar)) < 0)
		return (NULL);
	format += t;
	t = 0;
	if (*format == '.' && ++format)
		if ((t = check_valid_format_helper(format, env, *dollar)) < 0)
			return (NULL);
	format += t;
	return (format);
}

int		check_valid_format(char *format, t_env *env)
{
	char	*begin;
	int		dollar;

	begin = format;
	dollar = 0;
	format = check_valid_format_prehelper(format, env, &dollar);
	if (!format)
		return (-1);
	if (!ft_strncmp(format, "ll", 2) || !ft_strncmp(format, "hh", 2))
		format += 2;
	else if (char_in_string(*format, MODS))
		format++;
	if (char_in_string(*format, MODS) || (*format >= '0' && *format <= '9'))
		return (-1);
	if (char_in_string(*format, TYPES))
		env->max_arg_count += 1;
	else if (dollar)
		return (-1);
	if (*format != 0)
		format++;
	if (env->dollar >= 0 && env->dollar != dollar)
		return (-1);
	env->dollar = env->dollar < 0 ? dollar : (env->dollar | dollar);
	return (format - begin);
}
