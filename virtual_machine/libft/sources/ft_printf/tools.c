/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 18:08:02 by lbradama          #+#    #+#             */
/*   Updated: 2019/02/26 17:03:04 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_local.h"

int		char_in_string(char c, char *str)
{
	if (str)
		while (*str)
		{
			if (c == *str)
				return (1);
			str++;
		}
	return (0);
}

void	change_prepared(t_env *env, char **tmp, int width)
{
	free(env->cur->prepared);
	env->cur->prepared = *tmp;
	if (width >= 0)
		env->cur->len = width;
	else
		env->cur->len = ft_strlen(env->cur->prepared);
}

//char	*read_ull(char *str, unsigned long long int *n)
//{
//	int res;
//
//	res = 0;
//	while (*str >= '0' && *str <= '9')
//	{
//		res = res * 10;
//		res += *str - '0';
//		str++;
//	}
//	*n = res;
//	return (str);
//}

int		shift_int(char *str, int *n)
{
	int res;
	int i;

	res = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10;
		res += str[i] - '0';
		i++;
	}
	*n = res;
	return (i);
}

int		read_int_to_param(char *c, int *param, int shift)
{
	int i;
	int r;

	i = 0;
	r = 0;
	while (c[i] >= '0' && c[i] <= '9')
	{
		r *= 10;
		r += c[i] - '0';
		i++;
	}
	if (i > 0)
	{
		*param = r;
		return (i + shift);
	}
	return (shift);
}
