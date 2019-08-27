/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_s_h_flags.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 14:49:57 by ggerardy          #+#    #+#             */
/*   Updated: 2019/08/27 14:49:57 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void				ft_find_in_long(const char *ln, t_flags *fl)
{
	if (!ft_strncmp(ln, "silent", 7))
		SET_SILENT(fl->flags);
	else if (!ft_strncmp(ln, "help", 5))
		exit(ft_printf(g_help) * 0 + ft_free_flags(fl, 0));
	else if (ft_strncmp(ln, "output", 7))
	{
		ft_printf("%s\n", g_err_unknown_flag);
		ft_printf("%s\n", ln);
		fl->is_error = 1;
		ft_fdprintf(2, g_errors[UNKNOWN_FLAG], "--", 100, ln);
	}
}

static void				ft_find_in_shrt(const char *ln, t_flags *fl)
{
	while (*ln)
	{
		if (*ln == 's')
			SET_SILENT(fl->flags);
		else if (*ln == 'h')
			exit(ft_printf(g_help) * 0 + ft_free_flags(fl, 0));
		else if (*ln != 'o')
		{
			fl->is_error = 1;
			ft_fdprintf(2, g_errors[UNKNOWN_FLAG], "-", 1, ln);
		}
		++ln;
	}
}

t_flags					*ft_find_s_h_flags(int ac, char const *const *av)
{
	t_flags	*fl;
	int		i;

	if (ac == 1)
		return ((void *)(size_t)(ft_printf("%s", g_usage) * 0));
	if (!(fl = ft_make_flags()))
		return (0);
	i = 0;
	while (++i < ac && !fl->is_error)
	{
		if (av[i][0] == '-')
		{
			if (av[i][1] == '-')
				ft_find_in_long(av[i] + 2, fl);
			else
				ft_find_in_shrt(av[i] + 1, fl);
		}
	}
	return (fl);
}
