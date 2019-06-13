/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 17:07:24 by ggerardy          #+#    #+#             */
/*   Updated: 2019/06/13 17:07:24 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void 			ft_parse_l_flag(char *ln, t_flags *fl)
{

}

void			ft_parse_s_flag(char *ln, t_flags *fl)
{
	while (*ln)
	{
		if (*ln == 's')
		{
			if (fl->is_out)
				ft_fdprintf(2, "Missing output file after flag")
		}
	}
}

void 			ft_parse_path(char *ln, t_flags *fl, int is_out)
{
	if (!is_out)
	{
		if (!ft_vector_push_back(&fl->srcs, ln))
			exit(ft_free_flags(fl, 666));
	}
	else
	{
		if (!ft_vector_push_back(&fl->outputs, ln))
			exit(ft_free_flags(fl, 666));
	}
}

t_flags			*ft_parse_flags(int ac, char **av)
{
	t_flags	*fl;
	int 	i;

	if (ac == 1)
		return ((void*)(size_t)(ft_printf("%s", g_usage) * 0));
	if (!(fl = ft_make_flags()))
		return (0);
	i = 0;
	while (++i < ac)
	{
		if (av[i][0] == '-')
		{
			if (av[i][1] == '-')
				ft_parse_l_flag(av[i] + 2, fl);
			else
				ft_parse_s_flag(av[i] + 1, fl);
		}
	}
}