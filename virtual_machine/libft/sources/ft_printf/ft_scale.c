/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scale.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 19:24:08 by dwiegand          #+#    #+#             */
/*   Updated: 2019/02/24 13:41:58 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_local.h"

int			dectobin(t_plist *cur, uint64_t nbr, uint32_t size)
{
	uint32_t	i;

	i = size * 8 - 1;
	while (i > 0 && !(nbr >> i))
		i--;
	cur->len = i + 1;
	if (!(cur->prepared = malloc(sizeof(char) * (cur->len + 1))))
		return (0);
	while (i + 1)
	{
		*cur->prepared++ = ((nbr >> i) & 0x01) + (48);
		i--;
	}
	*cur->prepared = 0;
	cur->prepared -= cur->len;
	return (1);
}

int			dectobin_sharp(t_plist *cur, uint64_t nbr, uint32_t size)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	cur->len = size * 8 + size - 1;
	if (!(cur->prepared = malloc(sizeof(char) * (cur->len + 1))))
		return (0);
	while (i < size)
	{
		j = 0;
		while (j < 8)
		{
			cur->prepared[i * 8 + j] =
				((nbr >> (size * 8 - (i * 8 + j) - 1)) & 0x1) + (48);
			j++;
		}
		if (i + 1 != size)
			cur->prepared[i * 8 + j] = ' ';
		cur->prepared++;
		i++;
	}
	cur->prepared -= size;
	cur->prepared[cur->len] = 0;
	return (1);
}

int			llitoa(t_plist *cur, uint64_t nbr, int32_t sign)
{
	uint64_t	divider;
	int32_t		length;
	int32_t		i;

	i = 0;
	length = (nbr == 0 && cur->precision == 0) ? (0) : (1);
	divider = (nbr == 0 && cur->precision == 0) ? (0) : (1);
	if (!(nbr == 0 && cur->precision == 0))
		while (nbr / divider > 9 && ++length)
			divider *= 10;
	cur->len = (MAX(length, cur->precision)) + (sign != 0);
	if (!(cur->prepared = malloc(sizeof(char) * (cur->len + 1))))
		return (0);
	if (sign)
		*cur->prepared++ = sign;
	while (cur->precision - i > length)
		cur->prepared[i++] = (48);
	while (divider)
	{
		cur->prepared[i++] = nbr / divider % 10 + (48);
		divider /= 10;
	}
	cur->prepared[i] = 0;
	cur->prepared -= (sign != 0);
	return (1);
}

int			octal_base(t_env *env, uint64_t nbr)
{
	int32_t		i;
	int32_t		len;
	int32_t		precision;

	i = 0;
	len = 22;
	precision = env->cur->precision;
	while (len > 1 && !((nbr >> ((len - 1) * 3)) & 0x07))
		len--;
	env->cur->len = (MAX(len, env->cur->precision));
	if (!(env->cur->prepared = malloc(sizeof(char) * (env->cur->len + 1))))
		return (0);
	while (precision-- > len)
		*env->cur->prepared++ = (48);
	while (i < len)
	{
		env->cur->prepared[i] = ((nbr >> ((len - i - 1) * 3)) & 0x07) + '0';
		i++;
	}
	env->cur->prepared[i] = 0;
	env->cur->prepared -= (env->cur->len > len) ? (env->cur->len - len) : (0);
	return (1);
}

int			hex_base(t_env *env, uint64_t nbr, int32_t type)
{
	int32_t	i;
	int32_t	len;
	int32_t	c;
	int32_t	precision;

	i = 0;
	precision = env->cur->precision;
	len = 16;
	while (len > 1 && !((nbr >> ((len - 1) * 4)) & 0x0f))
		len--;
	env->cur->len = (MAX(len, env->cur->precision));
	if (!(env->cur->prepared = malloc(sizeof(char) * (env->cur->len + 1))))
		return (0);
	while (precision-- > len)
		*env->cur->prepared++ = (48);
	while (i < len)
	{
		c = (nbr >> ((len - i - 1) * (4))) & 0x0f;
		env->cur->prepared[i++] = (c < 10) ? (HEX[c]) : (HEX[c] - (type * 32));
	}
	env->cur->prepared[i] = 0;
	env->cur->prepared -= (env->cur->len > len) ? (env->cur->len - len) : (0);
	return (1);
}
