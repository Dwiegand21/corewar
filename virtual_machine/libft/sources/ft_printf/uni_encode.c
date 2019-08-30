/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uni_encode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 19:31:16 by dwiegand          #+#    #+#             */
/*   Updated: 2019/02/22 19:34:57 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_local.h"

uint32_t	encode_duo(uint32_t c)
{
	return (((c >> 6) | 0xC0) << 8 | ((c & 0x3F) | 0x80));
}

uint32_t	encode_tres(uint32_t c)
{
	return ((((c >> 12) | 0xE0) << 16) | ((((c >> 6) & 0x3F)
		| 0x80) << 8) | ((c & 0x3F) | 0x80));
}

uint32_t	encode_quat(uint32_t c)
{
	return ((((c >> 18) | 0xF0) << 24) | ((((c >> 12) & 0x3F)
		| 0x80) << 16) | ((((c >> 6) & 0x3F) | 0x80) << 8) | (c & 0x3F) | 0x80);
}

uint32_t	wchar_encode(uint32_t c)
{
	if (c <= 0x7FU)
		return (c);
	else if (c >= 0x80U && c <= 0x7FF)
		return ((encode_duo(c)));
	else if (c >= 0x800U && c <= 0xFFFF)
		return ((encode_tres(c)));
	else if (c >= 0x10000U && c <= 0x10FFFF)
		return ((encode_quat(c)));
	else
		return (0);
}

void		wstr_encode(uint32_t *array)
{
	uint32_t	i;

	i = 0;
	while (array[i])
	{
		array[i] = wchar_encode(array[i]);
		i++;
	}
}
