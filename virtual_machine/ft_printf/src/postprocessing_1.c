/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postprocessing_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 18:38:49 by lbradama          #+#    #+#             */
/*   Updated: 2019/02/26 17:05:27 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	post_int_helper(t_env *env, char *tmp, char sign)
{
	char	c;
	int		pos;

	if (env->cur->flags.minus)
	{
		ft_strcpy(tmp, (const char *)env->cur->prepared);
		ft_memset(&tmp[env->cur->len], ' ', env->cur->width - env->cur->len);
	}
	else
	{
		c = env->cur->flags.zero ? '0' : ' ';
		pos = env->cur->flags.zero && sign ? 1 : 0;
		ft_memset(&(tmp[pos]), c, env->cur->width - env->cur->len);
		ft_strcpy(&(tmp[env->cur->width - env->cur->len + pos]),
					(const char *)(env->cur->prepared + pos));
		if (env->cur->flags.zero)
			if (sign)
				tmp[0] = sign;
	}
}

int		post_int(t_env *env)
{
	char	sign;
	char	*tmp;

	sign = 0;
	if (env->cur->width > env->cur->len)
	{
		if (!env->cur->flags.minus)
		{
			if (env->cur->i < 0)
				sign = '-';
			else if (env->cur->flags.space)
				sign = ' ';
			else if (env->cur->flags.plus)
				sign = '+';
		}
		if (!(tmp = ft_strnew(env->cur->width + 1)))
			return (0);
		post_int_helper(env, tmp, sign);
		change_prepared(env, &tmp, -1);
	}
	return (1);
}

int		post_str(t_env *env)
{
	char	*tmp;
	char	c;

	c = ' ';
	if (env->cur->flags.zero && !env->cur->flags.minus)
		c = '0';
	if (env->cur->width > env->cur->len)
	{
		if (!(tmp = ft_strnew(env->cur->width + 1)))
			return (0);
		if (env->cur->flags.minus)
		{
			ft_strcpy(tmp, (const char *)env->cur->prepared);
			ft_memset(&tmp[env->cur->len], c, env->cur->width - env->cur->len);
		}
		else
		{
			ft_memset(tmp, c, env->cur->width - env->cur->len);
			ft_strcpy(&(tmp[env->cur->width - env->cur->len]),
						(const char *)env->cur->prepared);
		}
		change_prepared(env, &tmp, env->cur->width);
	}
	return (1);
}

int		post_char(t_env *env)
{
	char	*tmp;
	char	c;

	c = ' ';
	if (env->cur->flags.zero && !env->cur->flags.minus)
		c = '0';
	if (env->cur->width > env->cur->len)
	{
		if (!(tmp = ft_strnew(env->cur->width + 1)))
			return (0);
		if (env->cur->flags.minus)
		{
			ft_memcpy(tmp, (const char *)env->cur->prepared, env->cur->len);
			ft_memset(&tmp[env->cur->len], c, env->cur->width - env->cur->len);
		}
		else
		{
			ft_memset(tmp, c, env->cur->width - env->cur->len);
			ft_memcpy(&(tmp[env->cur->width - env->cur->len]),
						(const char *)env->cur->prepared, env->cur->len);
		}
		change_prepared(env, &tmp, env->cur->width);
	}
	return (1);
}

int		post_bin(t_env *env)
{
	char	*tmp;

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
		{
			ft_memset(tmp, ' ', env->cur->width - env->cur->len);
			ft_strcpy(&(tmp[env->cur->width - env->cur->len]),
						(const char *)env->cur->prepared);
		}
		change_prepared(env, &tmp, env->cur->width);
	}
	return (1);
}
