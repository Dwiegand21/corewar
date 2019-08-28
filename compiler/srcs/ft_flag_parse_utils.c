/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_parse_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 21:03:25 by ggerardy          #+#    #+#             */
/*   Updated: 2019/08/27 21:03:25 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_output_flag(t_flags *fl)
{
	char **input_ptr;

	if (!fl->was_input)
	{
		fl->is_error = 1;
		ft_fdprintf(2, g_is_silent ? "" : g_errors[MISSING_INPUT],
				"--output");
		return ;
	}
	fl->file_type = !fl->file_type;
	input_ptr = (char**)&fl->srcs->data[fl->srcs->len - 1];
	*input_ptr = (char*)((size_t)*input_ptr | (1lu << 63u));
}

void		ft_parse_l_flag(char *ln, t_flags *fl)
{
	if (!ft_strncmp(ln, "output", 7))
		ft_output_flag(fl);
	else if (ft_strncmp(ln, "silent", 7) &&
				ft_strncmp(ln, "help", 5))
	{
		fl->is_error = 1;
		ft_fdprintf(2, g_is_silent ? "" :
			g_errors[UNKNOWN_FLAG], "--", 100, ln);
	}
}

void		ft_parse_s_flag(char *ln, t_flags *fl)
{
	while (*ln)
	{
		if (*ln == 'o')
			ft_output_flag(fl);
		else if (*ln != 's' && *ln != 'h')
		{
			fl->is_error = 1;
			ft_fdprintf(2, g_is_silent ? "" :
				g_errors[UNKNOWN_FLAG], "-", 1, ln);
		}
		++ln;
	}
}

int			ft_ask(char *que, char *param[3])
{
	char b;

	b = 0;
	ft_fdprintf(2, que, param[0], param[1], param[2]);
	read(0, &b, 1);
	if (b == 'n' || b == 'N')
		return (0);
	return (1);
}

int			ft_isdir(char *name)
{
	struct stat statbuf;

	if (stat(name, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}
