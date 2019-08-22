/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 17:27:50 by lbradama          #+#    #+#             */
/*   Updated: 2019/02/26 17:32:17 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_local.h"

t_plist		*create_plist_node(void)
{
	t_plist *node;

	if (!(node = malloc(sizeof(t_plist))))
		return (NULL);
	node->original = NULL;
	node->prepared = NULL;
	node->original_width = -1;
	node->flags.minus = 0;
	node->flags.plus = 0;
	node->flags.space = 0;
	node->flags.sharp = 0;
	node->flags.zero = 0;
	node->flags.quote = 0;
	node->mod[0] = 0;
	node->mod[1] = 0;
	node->len = -1;
	node->width = -1;
	node->precision = -1;
	node->type = 0;
	node->type_pos = -1;
	node->width_pos = -1;
	node->precision_pos = -1;
	node->next = NULL;
	return (node);
}

int			args_init_creare(t_env *env, int count)
{
	if (!(env->args = malloc(sizeof(t_pargs))))
	{
		free_printf(env);
		return (0);
	}
	if (!(env->args->arg_list = malloc(sizeof(t_parg) * count)))
	{
		free_printf(env);
		return (0);
	}
	return (1);
}

int			args_init(t_env *env, int count, char *format)
{
	int		i;
	int		j;

	if (!args_init_creare(env, count))
		return (0);
	env->args->count = count;
	i = -1;
	while (++i < count)
	{
		j = -1;
		while (++j < 4)
			env->args->arg_list[i].type[j] = 0;
		env->args->arg_list[i].s = NULL;
		env->args->arg_list[i].ws = NULL;
	}
	env->args->arg_list[0].type[2] = 's';
	env->args->arg_list[0].read = 1;
	env->args->arg_list[0].s = format;
	env->args->cur = 1;
	i = 0;
	while (++i < count)
		env->args->arg_list[i].read = 0;
	return (1);
}

int			init_arg_list_helper(t_env *env, va_list *ap, t_pargs *a, int i)
{
	if (arg_cmp(a, i, "ll", "dDi"))
		a->arg_list[i].i = va_arg(*ap, long long int);
	else if (arg_cmp(a, i, "z", "dDi"))
		a->arg_list[i].i = va_arg(*ap, ssize_t);
	else if (arg_cmp(a, i, "j", "dDi"))
		a->arg_list[i].i = va_arg(*ap, intmax_t);
	else if (arg_cmp(a, i, "", "fF") || arg_cmp(a, i, "l", "fF"))
		a->arg_list[i].f = va_arg(*ap, double);
	else if (arg_cmp(a, i, "L", "fF"))
		a->arg_list[i].f = va_arg(*ap, long double);
	else if (arg_cmp(a, i, "", "s"))
		a->arg_list[i].s = va_arg(*ap, char *);
	else if (arg_cmp(a, i, "l", "s") || a->arg_list[i].type[2] == 'S')
		a->arg_list[i].ws = va_arg(*ap, unsigned int *);
	else if (arg_cmp(a, i, "", "cCdi") || arg_cmp(a, i, "h", "di") ||
		arg_cmp(a, i, "hh", "diC") || arg_cmp(a, i, "l", "c"))
		a->arg_list[i].i = va_arg(*ap, int);
	else if (arg_cmp(a, i, "l", "dDi") || arg_cmp(a, i, "", "D") ||
		arg_cmp(a, i, "h", "D") || arg_cmp(a, i, "hh", "D"))
		a->arg_list[i].i = va_arg(*ap, long int);
	else
		return (free_printf(env));
	return (1);
}

int			init_arg_list(t_env *env, va_list *ap)
{
	int		i;
	t_pargs	*a;

	a = env->args;
	i = 0;
	while (++i < a->count)
	{
		if (arg_cmp(a, i, "", "uboxX") || arg_cmp(a, i, "h", "uboxX") ||
			arg_cmp(a, i, "hh", "uboxX"))
			a->arg_list[i].i = va_arg(*ap, unsigned);
		else if (arg_cmp(a, i, "l", "uUoOxXbp") || arg_cmp(a, i, "", "UOp") ||
				arg_cmp(a, i, "h", "UO") || arg_cmp(a, i, "hh", "UO"))
			a->arg_list[i].i = va_arg(*ap, long unsigned);
		else if (arg_cmp(a, i, "ll", "uUoOxXb"))
			a->arg_list[i].i = va_arg(*ap, long long unsigned);
		else if (arg_cmp(a, i, "z", "uUoOxXb"))
			a->arg_list[i].i = va_arg(*ap, size_t);
		else if (arg_cmp(a, i, "j", "uoxXUO"))
			a->arg_list[i].i = va_arg(*ap, uintmax_t);
		else if (!init_arg_list_helper(env, ap, a, i))
			return (0);
	}
	return (1);
}
