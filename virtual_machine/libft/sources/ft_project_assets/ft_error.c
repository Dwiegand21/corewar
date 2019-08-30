/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 08:09:25 by axtazy            #+#    #+#             */
/*   Updated: 2019/08/23 05:26:04 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_project_assets.h"
#include "ft_iostream.h"
#include "ft_printf.h"

void	print_err_without_fname(
				char const *const format,
				...)
{
	va_list		va;

	va_start(va, format);
	ft_vdprintf(2, format, &va);
	va_end(va);
	exit(1);
}

void	print_err_with_fname(
				char const *restrict const function_name,
				char const *const format,
				...)
{
	va_list		va;

	va_start(va, format);
	ft_dprintf(2, "%s: ", function_name);
	ft_vdprintf(2, format, &va);
	va_end(va);
	exit(1);
}
