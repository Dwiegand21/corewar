/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbradama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 17:26:41 by lbradama          #+#    #+#             */
/*   Updated: 2019/02/26 17:26:25 by lbradama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_local.h"



int		ft_printf(const char *format, ...)
{
	va_list		va;
	int 		status;

	va_start(va, (char *)format);
	status = ft_vdprintf(1, format, &va);
	va_end(va);
	return (status);
}

int		ft_dprintf(int fd, const char *format, ...)
{
	va_list		va;
	int 		status;

	va_start(va, (char *)format);
	status = ft_vdprintf(fd, format, &va);
	va_end(va);
	return (status);
}

int		ft_fprintf(FILE *stream, const char *format, ...)
{
	va_list		va;
	int 		status;

	va_start(va, (char *)format);
	status = ft_vfprintf(stream, format, &va);
	va_end(va);
	return (status);
}

int 	ft_sprintf(char *buf, const char *format, ...)
{
	va_list		va;
	int 		status;

	va_start(va, (char *)format);
	status = ft_vsprintf(buf, format, &va);
	va_end(va);
	return (status);
}

int 	ft_asprintf(char **buf, const char *format, ...)
{
	va_list		va;
	int 		status;

	va_start(va, (char *)format);
	status = ft_vasprintf(buf, format, &va);
	va_end(va);
	return (status);
}

