/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigendian_ops.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 06:03:44 by axtazy            #+#    #+#             */
/*   Updated: 2019/06/02 06:12:41 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int32_t		be_get32(void *p)
{
	return ((((*((int32_t *)p) >> 0) & 0xFF) << 24)
			| (((*((int32_t *)p) >> 8) & 0xFF) << 16)
			| (((*((int32_t *)p) >> 16) & 0xFF) << 8)
			| (((*((int32_t *)p) >> 24) & 0xFF) << 0));
}

int16_t		be_get16(void *p)
{
	return ((((*((int16_t *)p) >> 0) & 0xFF) << 8)
			| (((*((int16_t *)p) >> 8) & 0xFF) << 0));
}

void		be_set32(void *p, int32_t value)
{
	*((int32_t *)p) = ((((value >> 0) & 0xFF) << 24)
			| (((value >> 8) & 0xFF) << 16)
			| (((value >> 16) & 0xFF) << 8)
			| (((value >> 24) & 0xFF) << 0));
}

void		be_set16(void *p, int16_t value)
{
	*((int16_t *)p) = ((((value >> 0) & 0xFF) << 8)
			| (((value >> 8) & 0xFF) << 0));
}