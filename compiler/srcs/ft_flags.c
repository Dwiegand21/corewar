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

void		ft_parse_filename(char *ln, t_flags *fl)
{
	char *ext;

	ext = ft_rstrchr(ln, '.');
	ext = !ext ? ln + ft_strlen(ln) : ext;
	if (!ft_strcmp(ext, fl->file_type == INPUT ? ".s" : ".cor"))
		ft_vector_push_back(
				fl->file_type == INPUT ? &fl->srcs : &fl->outputs, ln);
	else if ((fl->file_type == OUTPUT && ft_isdir(ln)) ||
			(GET_SILENT(fl->flags) || ft_ask(g_errors[WRG_EXT],
			(char*[3]){fl->file_type == INPUT ? "input" : "output", ln,
			fl->file_type == INPUT ? ".s" : ".cor"})))
		ft_vector_push_back(
				fl->file_type == INPUT ? &fl->srcs : &fl->outputs, ln);
	else
		exit(ft_free_flags(fl, 0));
	fl->was_input = fl->file_type == INPUT;
	fl->file_type = INPUT;
}

t_flags		*ft_parse_flags(t_flags *fl, int ac, char **av)
{
	int i;

	i = 0;
	while (++i < ac && !fl->is_error)
	{
		if (av[i][0] == '-')
		{
			if (av[i][1] == '-')
				ft_parse_l_flag(av[i] + 2, fl);
			else
				ft_parse_s_flag(av[i] + 1, fl);
		}
		else if (!fl->is_error)
		{
			ft_parse_filename(av[i], fl);
		}
	}
	g_is_silent = GET_SILENT(fl->flags);
	return (fl);
}
