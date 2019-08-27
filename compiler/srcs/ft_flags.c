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

static inline void			ft_output_flag(t_flags *fl)
{
	char **input_ptr;

	if (!fl->was_input)
	{
		fl->is_error = 1;
		ft_fdprintf(2, g_errors[MISSING_INPUT], "--output");
		return ;
	}
	fl->file_type = !fl->file_type;
	input_ptr = (char**)&fl->srcs->data[fl->srcs->len - 1];
	*input_ptr = (char*)((size_t)*input_ptr | (1lu << 63u));
}

static inline void 			ft_parse_l_flag(char *ln, t_flags *fl)
{
	if (!ft_strncmp(ln, "output", 7))
		ft_output_flag(fl);
}

static inline void			ft_parse_s_flag(char *ln, t_flags *fl)
{
	while (*ln)
	{
		if (*ln == 'o')
			ft_output_flag(fl);
		++ln;
	}
}

static inline int	ft_ask(char *que, char *param[3])
{
	char b;

	b = 0;
	ft_fdprintf(2, que, param[0], param[1], param[2]);
	read(0, &b, 1);
	if (b == 'n' || b == 'N')
		return (0);
	return (1);
}

static inline int	ft_isdir(char *name)
{
	struct stat statbuf;
	if (stat(name, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

void 				ft_parse_filename(char *ln, t_flags *fl)
{
	char	*ext;

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

t_flags				*ft_parse_flags(t_flags	*fl, int ac, char **av)
{
	int 	i;

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
	return (fl);
}