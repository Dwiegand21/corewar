/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 19:44:22 by ggerardy          #+#    #+#             */
/*   Updated: 2019/05/25 19:44:22 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		*ft_get_lbl_name(t_champ *champ, char **s, char *stop_chars)
{
	char			*str;
	t_string		*res;
	char 			*bad_char;

	bad_char = 0;
	if (!s || !*s || !(res = ft_make_string(8)))
		return (0);
	while (!ft_strchr(stop_chars, **s) && !ft_isspace(**s) && **s) // todo check COMMENT_CHAR +?
	{
		if (!ft_strchr(LABEL_CHARS, **s))
			bad_char = bad_char ? bad_char : *s;
		if (!ft_string_push_back(&res, **s))
			exit(ft_free_champ(&champ, 13));
		++(*s);
	}
	str = res->data;
	free(res);
	if (bad_char)
		ft_make_error(WRONG_CHAR_LBL, champ, bad_char - champ->curr_line + 1,
					  (void*[4]){bad_char, str, 0, 0});
	return (str);
}

int 		ft_is_command(char *line)
{
	int i;

	i = -1;
	while (++i < 16)
	{
		if (!ft_strncmp(line, g_functions[i].name, g_functions[i].namelen))
		{
			return (i);
		}
	}
	return (-1);
}

static inline unsigned int	ft_get_arg_type(char **ln)
{
	if (**ln == DIRECT_CHAR)
	{
		ft_skip_spaces(ln);
		if (**ln == LABEL_CHAR )
		{
			++(*ln);
			ft_skip_spaces(ln);
			return (T_LAB);
		}
		else
			return (T_DIR);
	}
	else if (**ln == 'r')
	{
		++(*ln);
		ft_skip_spaces(ln);
		return (T_REG);
	}
	else
		return (T_IND);
}

static inline void		*ft_get_arg_val(char **ln, unsigned int type,
		t_champ *champ, const char *begin)
{
	void		*arg;
	char		*first_char;
	char		*bad_arg;

	bad_arg = 0;
	first_char = *ln;
	arg = (type != T_LAB) ? (void*)(size_t)ft_atoi_m(ln) :
			ft_get_lbl_name(champ, ln,
					(char[3]){COMMENT_CHAR, SEPARATOR_CHAR, '\0'});
	if (type != T_LAB && ((!ft_isdigit(*first_char) ||
		(!ft_isspace(**ln) && **ln != SEPARATOR_CHAR && **ln != COMMENT_CHAR))))
		bad_arg = *ln;
	while (!ft_isspace(**ln) && **ln != SEPARATOR_CHAR && **ln != COMMENT_CHAR
		&& **ln)
		++(*ln);
	if (bad_arg)
		ft_make_error(BAD_ARG, champ, bad_arg - champ->curr_line,
				(void*[4]){*ln - *begin, (void*)begin, 0, 0});
	if (type == T_REG && (int)(size_t)arg <= 0)
		ft_make_error(BAD_REG_IDX, champ, begin - champ->curr_line,
				(void*[4]){*ln - *begin, (void*)begin, 0, 0});
	return (arg);
}

int			ft_parse_arg(t_champ *champ, t_cmd *cmd, char **ln)
{
	char *const			begin = *ln;
	const unsigned char	type = ft_get_arg_type(ln);
	void *const			val = ft_get_arg_val(ln, type, champ, begin);
	char 				*sep;

	cmd->arg_types[cmd->arg_count] = type;
	cmd->args[cmd->arg_count] = val;
	++cmd->arg_count;
	ft_skip_spaces(ln);
	if (!**ln || **ln == COMMENT_CHAR)
	{
		if (cmd->arg_count != g_functions[cmd->cmd].arg_count)
			ft_make_error(BAD_ARG_COUNT, champ, *ln - champ->curr_line,
				(void*[4]){g_functions[cmd->cmd].name,
				(void*)(size_t)g_functions[cmd->cmd].arg_count,
				(void*)(size_t)cmd->arg_count, 0});
		return (0);
	}
	sep = (**ln == SEPARATOR_CHAR) ? *ln : 0;
	(*ln) += (sep != 0);
	ft_skip_spaces(ln);
	if (!sep)
		ft_make_error(MISSING_SEP, champ, *ln - champ->curr_line,
				(void*[4]){(void*)(size_t)SEPARATOR_CHAR, 0, 0, 0});
	if (!**ln || **ln == COMMENT_CHAR)
	{
		ft_make_error(EXTRA_SEP, champ, sep - champ->curr_line,
				(void*[4]){(void*)(size_t)SEPARATOR_CHAR, 0, 0, 0});
		return (0);
	}
// todo throw error about extra args and return 0
	return (1);
}

void 		ft_parse_command(t_champ *champ, char *ln, int cmd_num)
{
	t_cmd *cmd;

	if (!(cmd = (t_cmd*)ft_memalloc(sizeof(t_cmd))))
		exit(ft_free_champ(&champ, 666));
	cmd->cmd = (unsigned char)cmd_num;
	ln += g_functions[cmd_num].namelen;
	ft_skip_spaces(&ln);



	// todo need parse command
	// todo need to save in champion current memory-address
	// todo and use vector with labels for 'join' them with current command

}

size_t		ft_find_bad_cmd_len(char *ln)
{
	size_t len;

	len = 0;
	while (*ln && *ln != SEPARATOR_CHAR && !ft_isspace(*ln))
	{
		++ln;
		++len;
	}
	return (len);
}

void 		ft_add_label(t_champ *champ, char *lbl, char *ln)
{
	void **map_val;
	if (!(map_val = ft_map_get(champ->labels, lbl)))
		exit(ft_free_champ(&champ, 666));
	if (*map_val != champ->labels->nil)
	{
		ft_make_error(MULT_LABEL, champ,
			(int)(ln - ft_strlen(lbl) - (size_t)champ->curr_line + 1),
			(void *[4]){lbl, 0, 0, 0});
		free(lbl);
	}
	else
		*map_val = (void*)(size_t)-1;
	if (!ft_vector_push_back(&champ->current_labels, lbl))
		exit(ft_free_champ(&champ, 666));
}

void 		ft_parse_label(t_champ *champ, char *ln)
{
	char	*label;
	int 	cmd;

	label = ft_get_lbl_name(champ, &ln, (char[3]){COMMENT_CHAR, LABEL_CHAR, '\0'});
	ft_skip_spaces(&ln);
	if (*ln != LABEL_CHAR)
		ft_make_error(MISS_LBL_CHAR, champ, ln - champ->curr_line + 1,
					  (void*[4]){(void*)(size_t)LABEL_CHAR, label, 0, 0});
	ft_add_label(champ, label, ln);
	ln += (*ln && *ln == LABEL_CHAR);
	while (ft_isspace(*ln))
		++ln;
	if (*ln && (cmd = ft_is_command(ln)) >= 0)
		ft_parse_command(champ, ln, cmd);
	else if (*ln)
		ft_make_error(BAD_CMD, champ, ln - champ->curr_line + 1,
					  (void*[4]){(void*)ft_find_bad_cmd_len(ln), ln, 0, 0});
}

void 		ft_parse_line(t_champ *champ, char *ln)
{
	int cmd;

	if (!*ln)
		return ;
	ft_skip_spaces(&ln);
	if (*ln == COMMENT_CHAR)
		return ;
	if ((cmd = ft_is_command(ln)) >= 0)
		ft_parse_command(champ, ln, cmd);
	else
		ft_parse_label(champ, ln);

}

void 		ft_parse_exec(t_champ *champ, int fd)
// todo expect comments in mid of label or arg FUCK
{
	char *ln;

	ft_parse_line(champ, champ->curr_line);
	while ((ln = (void*)1lu) && ft_get_next_line(fd, &ln, BUFF_SIZE) &&
		   ++champ->line)
	{
		if (!ln)
			exit(ft_free_champ(&champ, 13));
		ft_champ_upd_line(champ, ln);
		ft_parse_line(champ, ln);
	}
}

t_champ 	*ft_parser(char *file)
{
	t_champ *champ;
	int fd;

	if ((fd = open(file, O_RDONLY)) == -1) // todo check extension
		return (0);
	if (!(champ = ft_make_champ(file, fd)))
		return (0);
	ft_parse_header(champ, fd);
	ft_parse_exec(champ, fd);

	ft_printf("<%s>\n", champ->name->data);
	ft_printf("<%s>\n", champ->comment->data);
	ft_printf("<%s>\n", champ->curr_line);



	return (champ);
}

