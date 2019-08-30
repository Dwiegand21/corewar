/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 15:01:31 by dwiegand          #+#    #+#             */
/*   Updated: 2019/08/28 15:01:31 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_FT_PRINTF_H
# define LIBFT_FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>

int		ft_printf(const char *format, ...);
int		ft_dprintf(int fd, const char *format, ...);
int		ft_fprintf(FILE *stream, const char *format, ...);
int		ft_sprintf(char *buf, const char *format, ...);
int		ft_asprintf(char **buf, const char *format, ...);

int		ft_vprintf(const char *format, va_list *va);
int		ft_vdprintf(int fd, const char *format, va_list *va);
int		ft_vfprintf(FILE *stream, const char *format, va_list *va);
int		ft_vsprintf(char *buf, const char *format, va_list *va);
int		ft_vasprintf(char **buf, const char *format, va_list *va);

#endif
