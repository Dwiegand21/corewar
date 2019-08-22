/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 19:12:18 by lbradama          #+#    #+#             */
/*   Updated: 2019/02/26 17:31:32 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		set_color(char *c, t_plist *cur, int len)
{
	cur->original = ft_strdup(c);
	cur->original_width = ft_strlen(cur->original);
	return (len);
}

int		is_color(char *c, t_plist *cur)
{
	if (!ft_strncmp(c, "{red}", 5))
		return (set_color(RED, cur, 5));
	if (!ft_strncmp(c, "{green}", 7))
		return (set_color(GREEN, cur, 7));
	if (!ft_strncmp(c, "{yellow}", 8))
		return (set_color(YELLOW, cur, 8));
	if (!ft_strncmp(c, "{blue}", 6))
		return (set_color(BLUE, cur, 6));
	if (!ft_strncmp(c, "{magenta}", 9))
		return (set_color(MAGENTA, cur, 9));
	if (!ft_strncmp(c, "{cyan}", 6))
		return (set_color(CYAN, cur, 6));
	if (!ft_strncmp(c, "{reset}", 7))
		return (set_color(RESET, cur, 7));
	return (0);
}

int		is_flag(char c, t_plist *cur)
{
	if (c == '-')
		return (cur->flags.minus = 1);
	if (c == '+')
		return (cur->flags.plus = 1);
	if (c == ' ')
		return (cur->flags.space = 1);
	if (c == '#')
		return (cur->flags.sharp = 1);
	if (c == '0')
		return (cur->flags.zero = 1);
	if (c == '\'')
		return (cur->flags.quote = 1);
	return (0);
}

int		is_modifier(char *c, t_plist *cur)
{
	if ((c[0] == 'l' && c[1] == 'l') || (c[0] == 'h' && c[1] == 'h'))
	{
		cur->mod[0] = c[0];
		cur->mod[1] = c[1];
		return (2);
	}
	if (char_in_string(c[0], MODS))
	{
		cur->mod[0] = c[0];
		return (1);
	}
	return (0);
}

int		is_type(char c, t_env *env)
{
	int i;

	i = 0;
	while (TYPES[i])
	{
		if (c == TYPES[i])
		{
			env->cur->type = c;
			if (env->cur->type_pos == -1)
			{
				env->cur->type_pos = env->args->cur;
				env->args->arg_list[env->args->cur].type[0] = env->cur->mod[0];
				env->args->arg_list[env->args->cur].type[1] = env->cur->mod[1];
				env->args->arg_list[env->args->cur].type[2] = env->cur->type;
				env->args->cur = env->args->cur + 1;
			}
			return (1);
		}
		i++;
	}
	env->cur->type = '%';
	env->cur->i = c;
	return (c != 0);
}
