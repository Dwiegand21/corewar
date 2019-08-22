/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 19:41:44 by dwiegand          #+#    #+#             */
/*   Updated: 2019/02/24 18:39:23 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			wchar_transformation(t_env *env, uint32_t c)
{
	uint32_t	i;
	uint32_t	res;
	uint32_t	length;

	i = 0;
	length = 4;
	res = wchar_encode(c);
	while (length > 1 && !(res >> ((length - 1) * 8)))
		length--;
	env->cur->len = length;
	if (!(env->cur->prepared = malloc(sizeof(char) * (length + 1))))
		return (0);
	env->cur->prepared[length] = 0;
	while (i < length)
	{
		env->cur->prepared[i] = (char)((res >> (length - i - 1) * 8) & 0xFF);
		i++;
	}
	return (1);
}

int			str_transformation(t_plist *cur, char *str)
{
	int32_t		i;
	int32_t		null;

	null = 0;
	if (!str)
	{
		null = 1;
		str = "(null)";
	}
	if (cur->precision < 0)
		cur->len = ft_strlen(str);
	else
		cur->len = MIN(ft_strlen(str), (unsigned)cur->precision);
	if (!(cur->prepared = malloc(sizeof(char) * (cur->len + 1))))
		return (0);
	cur->prepared[cur->len] = 0;
	i = -1;
	while (++i < cur->len)
		cur->prepared[i] = str[i];
	if (null)
		str = NULL;
	return (1);
}

void		precision_check(char **array, int32_t *length, int32_t precision)
{
	int32_t		i;

	i = 0;
	if (precision != -1 && *length > precision)
	{
		*length = precision;
		if ((((*array)[*length - 1]) & 0x80))
		{
			while (((*array)[*length] & 0xC0) == 0x80)
				*length -= 1;
		}
		(*array)[*length] = 0;
	}
}

int			lstr_tramsformation_helper(t_env *env, uint32_t *str)
{
	uint32_t	*copy;
	uint32_t	cur_length;

	cur_length = 0;
	while (str[cur_length])
		cur_length++;
	if (!(copy = wstrdup(str, cur_length)))
		return (0);
	wstr_encode(copy);
	env->cur->len = wstr_len(copy);
	if (!(env->cur->prepared = malloc(sizeof(char) * (env->cur->len + 1))))
	{
		free(copy);
		return (0);
	}
	wstr_cpy(env->cur->prepared, copy, (uint32_t)env->cur->len);
	free(copy);
	return (1);
}

int			lstr_tramsformation(t_env *env, uint32_t *str)
{
	if (!str)
	{
		if (!(env->cur->prepared = ft_strdup("(null)")))
			return (0);
		env->cur->len = 6;
	}
	else if (!lstr_tramsformation_helper(env, str))
		return (0);
	precision_check(&env->cur->prepared, &env->cur->len, env->cur->precision);
	return (1);
}
