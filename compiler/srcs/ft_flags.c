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

/**
 *
 *  ./asm  /path/to/gg.s  ...                                    =>  /path/to/gg.cor ...
 *  ./asm  /path/to/gg.s -o gg.cor  /path/to/ff.s -o ff.cor ...  =>  gg.cor ff.cor ...
 *
 **/

/**
 *
 * Flags:
 * -o (--output) : specify output file
 * -s (--silent) : silent mode
 * -h (--help)   : print usage
 *
 **/

static inline void	ft_output_flag(t_flags *fl)
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

void 			ft_parse_l_flag(char *ln, t_flags *fl)
{
	if (!ft_strncmp(ln, "output", 7))
		ft_output_flag(fl);
	else if (!ft_strncmp(ln, "silent", 7))
		SET_SILENT(fl->flags);
	else if (!ft_strncmp(ln, "help", 5))
		SET_HELP(fl->flags);
	else
	{
		ft_printf("%s\n", g_err_unknown_flag);
		ft_printf("%s\n", ln);
		fl->is_error = 1;
		ft_fdprintf(2, g_errors[UNKNOWN_FLAG], "--", 100, ln);
	}
}

void			ft_parse_s_flag(char *ln, t_flags *fl)
{
	while (*ln)
	{
		if (*ln == 'o')
			ft_output_flag(fl);
		else if (*ln == 's')
			SET_SILENT(fl->flags);
		else if (*ln == 'h')
			SET_HELP(fl->flags);
		else
		{
			fl->is_error = 1;
			ft_fdprintf(2, g_errors[UNKNOWN_FLAG], "-", 1, ln);
		}
		++ln;
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

void 			ft_parse_filename(char *ln, t_flags *fl)
{
	char	*ext;
	int		filename_len;

	ext = ft_rstrchr(ln, '.');
	ext = !ext ? ln + ft_strlen(ln) : ext;
	filename_len = (int)(ext - ln);

	if (filename_len > MAX_FILENAME_LEN)
		exit(1); // todo free all

	if (!ft_strcmp(ext, fl->file_type == INPUT ? ".s" : ".cor"))
		ft_vector_push_back(
				fl->file_type == INPUT ? &fl->srcs : &fl->outputs, ln);
	else if (GET_SILENT(fl->flags) || ft_ask(g_errors[WRG_EXT],
			(char*[3]){fl->file_type == INPUT ? "input" : "output", ln,
			  fl->file_type == INPUT ? ".s" : ".cor"}))
		ft_vector_push_back(
				fl->file_type == INPUT ? &fl->srcs : &fl->outputs, ln);
	else
		exit(0); // todo free all
	fl->was_input = fl->file_type == INPUT;
	fl->file_type = INPUT;
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
	ft_printf("Parsed: %#hhB\n", fl->flags);
	ft_printf("Srcs:\n");
	for (size_t e = 0; e < fl->srcs->len; ++e)
		ft_printf("%s\n", (size_t)fl->srcs->data[e] & ~(1lu << 63u));
	ft_printf("Outs:\n");
	for (size_t e = 0; e < fl->outputs->len; ++e)
		ft_printf("%s\n", fl->outputs->data[e]);
	return (fl);
}