/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postprocessing_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 18:38:49 by lbradama          #+#    #+#             */
/*   Updated: 2019/02/26 17:06:26 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_local.h"

int		post_hex_prehelper(t_env *env, char *pre, char *tmp, int *skip)
{
	if (env->cur->type == 'p')
		pre = "0x";
	if (env->cur->flags.sharp)
	{
		if (env->cur->prepared[0] != '0' &&
			(env->cur->type == 'o' || env->cur->type == 'O'))
			pre = "0";
		else if (env->cur->i != 0 && env->cur->type == 'x')
			pre = "0x";
		else if (env->cur->i != 0 && env->cur->type == 'X')
			pre = "0X";
	}
	else if (env->cur->flags.sharp && !env->cur->len)
		if (env->cur->type == 'o' || env->cur->type == 'O')
			pre = "0";
	if (pre)
	{
		*skip = ft_strlen(pre);
		if (!(tmp = ft_strnew(env->cur->len + 1 + *skip)))
			return (0);
		ft_strcat(tmp, pre);
		ft_strcat(tmp, env->cur->prepared);
		change_prepared(env, &tmp, env->cur->len + *skip);
	}
	return (1);
}

void	post_hex_helper(t_env *env, int skip, char *tmp)
{
	if (env->cur->flags.zero)
	{
		if (skip)
			tmp[0] = env->cur->prepared[0];
		if (skip - 1 > 0)
			tmp[1] = env->cur->prepared[1];
		ft_memset(&(tmp[skip]), '0', env->cur->width - env->cur->len);
		ft_strcat(tmp, (const char *)(&env->cur->prepared[skip]));
	}
	else
	{
		ft_memset(tmp, ' ', env->cur->width - env->cur->len);
		ft_strcat(tmp, (const char *)env->cur->prepared);
	}
}

int		post_hex(t_env *env)
{
	char	*pre;
	char	*tmp;
	int		skip;

	pre = NULL;
	tmp = NULL;
	skip = 0;
	if (!post_hex_prehelper(env, pre, tmp, &skip))
		return (0);
	if (env->cur->width > env->cur->len)
	{
		if (!(tmp = ft_strnew(env->cur->width + 1)))
			return (0);
		if (env->cur->flags.minus)
		{
			ft_strcpy(tmp, (const char *)env->cur->prepared);
			ft_memset(&tmp[env->cur->len], ' ',
						env->cur->width - env->cur->len);
		}
		else
			post_hex_helper(env, skip, tmp);
		change_prepared(env, &tmp, env->cur->width);
	}
	return (1);
}

void	post_float_helper(t_env *env, char *tmp)
{
	char	sign;
	char	c;
	int		pos;

	sign = 0;
	if (env->cur->f < 0)
		sign = '-';
	else if (env->cur->flags.plus)
		sign = '+';
	else if (env->cur->flags.space)
		sign = ' ';
	c = env->cur->flags.zero ? '0' : ' ';
	pos = env->cur->flags.zero && sign ? 1 : 0;
	ft_memset(&(tmp[pos]), c, env->cur->width - env->cur->len);
	ft_strcpy(&(tmp[env->cur->width - env->cur->len + pos]),
			(const char *)(env->cur->prepared + pos));
	if (env->cur->flags.zero)
		if (sign)
			tmp[0] = sign;
}

int		post_float(t_env *env)
{
	char	*tmp;
	int		c;

	c = -1;
	while (++c < env->cur->len)
		if ((env->cur->prepared[c] >= 'a' && env->cur->prepared[c] <= 'z') ||
			(env->cur->prepared[c] >= 'A' && env->cur->prepared[c] <= 'Z'))
			env->cur->flags.zero = 0;
	c = ' ';
	if (env->cur->width > env->cur->len)
	{
		if (!(tmp = ft_strnew(env->cur->width + 1)))
			return (0);
		if (!env->cur->flags.minus)
			post_float_helper(env, tmp);
		else
		{
			ft_strcpy(tmp, (const char *)env->cur->prepared);
			ft_memset(&tmp[env->cur->len], ' ',
						env->cur->width - env->cur->len);
		}
		change_prepared(env, &tmp, env->cur->width);
	}
	return (1);
}
