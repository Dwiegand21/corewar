/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 17:26:41 by lbradama          #+#    #+#             */
/*   Updated: 2019/02/26 17:26:25 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_result(t_plist *cur)
{
	int res;

	res = 0;
	while (cur)
	{
		if (cur->original)
		{
			res += cur->original_width;
			write(1, cur->original, cur->original_width);
		}
		else
		{
			res += cur->len;
			write(1, cur->prepared, cur->len);
		}
		cur = cur->next;
	}
	return (res);
}

int		free_printf(t_env *env)
{
	t_plist *tmp;

	if (env)
	{
		if (env->args)
		{
			if (env->args->arg_list)
				free(env->args->arg_list);
			free(env->args);
		}
		while (env->plist)
		{
			tmp = env->plist->next;
			if (env->plist->prepared)
				free(env->plist->prepared);
			free(env->plist);
			env->plist = tmp;
		}
		free(env);
	}
	return (0);
}

t_env	*init_env(void)
{
	t_env	*env;

	env = NULL;
	if (!(env = malloc(sizeof(t_env))))
		env = NULL;
	env->args = NULL;
	env->plist = NULL;
	env->cur = NULL;
	env->max_arg_count = 0;
	env->max_arg_pos = 0;
	env->dollar = -1;
	env->error = 0;
	return (env);
}

int		ft_printf_init(const char *format, t_env *env)
{
	int		args_count;

	args_count = get_args_count(env, (char *)format);
	if (args_count < 0)
		return (0);
	if (!args_init(env, args_count + 1, (char *)format))
		return (0);
	if (!(env->plist = create_plist_node()))
	{
		free_printf(env);
		return (0);
	}
	format_analysis(env, (char *)format);
	return (1);
}

int		ft_printf(const char *format, ...)
{
	int		res;
	t_env	*env;
	va_list	ap;

	if (!*format)
		return (0);
	if (!(env = init_env()))
		return (0);
	if (!ft_printf_init(format, env))
		return (-1);
	va_start(ap, (char *)format);
	if (!init_arg_list(env, &ap))
		return (-1);
	va_end(ap);
	if (!prepare_plist(env))
	{
		free_printf(env);
		return (-1);
	}
	res = print_result(env->plist);
	free_printf(env);
	return (res);
}
