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

	i = 16;
	while (--i >= 0)
	{
		if (!ft_strncmp(line, g_functions[i].name, g_functions[i].namelen))
		{
			return (i);
		}
	}
	return (-1);
}

static inline int	ft_check_arg(t_champ *champ, char **ln, char *begin,
		int type)
{
	char *lbl_pref_end;

	if (!(!**ln || **ln == SEPARATOR_CHAR || **ln == COMMENT_CHAR ||
			**ln == ALT_CMT_CHAR))
		return (type);
	if (type == T_DIR || type == T_REG)
		ft_make_error(MISS_ARG_AFT_PRFX, champ, begin - champ->curr_line + 1,
				(void*[4]){g_nbrs[champ->curr_cmd->arg_count + 1],
			   (void*)1lu, begin, g_functions[champ->curr_cmd->cmd].name});
	if (type == T_IND &&
	 champ->curr_cmd->arg_count < g_functions[champ->curr_cmd->cmd].arg_count)
		ft_make_error(MISS_ARG, champ, begin - champ->curr_line + 1, // fixme
				(void*[4]){g_nbrs[champ->curr_cmd->arg_count + 1],
				g_functions[champ->curr_cmd->cmd].name, 0, 0});
	if (type == T_LAB && (lbl_pref_end = begin))
	{
		while (*lbl_pref_end != LABEL_CHAR)
			++lbl_pref_end;
		ft_make_error(MISS_ARG_AFT_PRFX, champ, begin - champ->curr_line + 1, // fixme
				(void*[4]){g_nbrs[champ->curr_cmd->arg_count + 1],
				(void*)(lbl_pref_end - begin + 1), begin,
				g_functions[champ->curr_cmd->cmd].name});
	}
	return (-1 * type);
}

static inline int	ft_get_arg_type(char **ln, t_champ *champ)
{
	char *const begin = *ln;

	if (**ln == DIRECT_CHAR && ++(*ln))
	{
		ft_skip_spaces(ln);
		if (**ln == LABEL_CHAR && ++(*ln))
		{
			champ->curr_cmd->lbl_line = champ->line;
			ft_skip_spaces(ln);
			if (champ->curr_cmd->arg_count <
			        g_functions[champ->curr_cmd->cmd].arg_count)
				champ->curr_cmd->lbl_poses[champ->curr_cmd->arg_count] =
					*ln - champ->curr_line;
			return (ft_check_arg(champ, ln, begin, T_LAB));
		}
		else
			return (ft_check_arg(champ, ln, begin, T_DIR));
	}
	else if (**ln == 'r' && ++(*ln))
	{
		ft_skip_spaces(ln);
		return (ft_check_arg(champ, ln, begin, T_REG));
	}
	else
		return (ft_check_arg(champ, ln, begin, T_IND));
}

static inline void		*ft_get_arg_val(char **ln, int type,
		t_champ *champ, const char *begin)
{
	void		*arg;
	char		*bad_arg;

	if (type < 0)
		return (0);
	bad_arg = 0;
	arg = (type != T_LAB) ? (void*)(size_t)ft_atoi_m(ln) :
			ft_get_lbl_name(champ, ln,
				(char[4]){COMMENT_CHAR, SEPARATOR_CHAR, ALT_CMT_CHAR, '\0'});
	if (type != T_LAB && **ln != SEPARATOR_CHAR && **ln != COMMENT_CHAR &&
			**ln != ALT_CMT_CHAR && **ln && !ft_isspace(**ln))
		bad_arg = *ln; // fixme
	while (!ft_isspace(**ln) && **ln != SEPARATOR_CHAR && **ln != COMMENT_CHAR
		&& **ln != ALT_CMT_CHAR && **ln)
		++(*ln);
	if (bad_arg)
		ft_make_error(BAD_ARG, champ, bad_arg - champ->curr_line + 1,
				(void*[4]){(void*)(*ln - begin), (void*)begin, 0, 0});
	if (type == T_REG && (int)(size_t)arg <= 0)
		ft_make_error(BAD_REG_IDX, champ, begin - champ->curr_line + 1,
				(void*[4]){(void*)(*ln - begin), (void*)begin, 0, 0});
	if (type == T_LAB &&
	champ->curr_cmd->arg_count >= g_functions[champ->curr_cmd->cmd].arg_count)
		free(arg);
	return (arg);
}

static inline int 		ft_move_to_next_arg(t_champ *champ, char **ln)
{
	char 				*sep;

	sep = (**ln == SEPARATOR_CHAR) ? *ln : 0;
	((*ln) += (sep != 0));
	ft_skip_spaces(ln);
	if (!sep)
		ft_make_error(MISSING_SEP, champ, *ln - champ->curr_line + 1,
					  (void*[4]){(void*)(size_t)SEPARATOR_CHAR, 0, 0, 0});
	if ((!**ln || **ln == COMMENT_CHAR || **ln == ALT_CMT_CHAR ||
	**ln == SEPARATOR_CHAR) &&
	champ->curr_cmd->arg_count >= g_functions[champ->curr_cmd->cmd].arg_count)
	{
		ft_make_error(EXTRA_SEP, champ, sep - champ->curr_line + 1,
					  (void *[4]) {(void *) (size_t) SEPARATOR_CHAR, 0, 0, 0});
		champ->curr_cmd->arg_count -=
			champ->curr_cmd->arg_count >
			g_functions[champ->curr_cmd->cmd].arg_count;
	}
	return ((!**ln || **ln == COMMENT_CHAR || **ln == ALT_CMT_CHAR) ? 0 : 1); // todo no need return anymore
}

static inline void	ft_check_arg_type_for_op(t_champ *champ, t_cmd *cmd,
		int type, char *begin)
{
	if (type == -1 * (int)T_IND)
		return ;
	type = (type < 0) ? type * -1 : type;
	type = (type == T_LAB) ? T_DIR : type;
	if ((unsigned)type & g_functions[cmd->cmd].arg[cmd->arg_count - 1])
		return ;
	ft_make_error(BAD_ARG_TYPE, champ, begin - champ->curr_line + 1,
			(void*[4]){g_nbrs[cmd->arg_count], g_functions[cmd->cmd].name,
			  g_types[g_functions[cmd->cmd].arg[cmd->arg_count - 1] - 1],
			  g_types[type - 1]});
}

int			ft_parse_arg(t_champ *champ, t_cmd *cmd, char **ln)
{
	char *const	begin = *ln;
	const int	type = ft_get_arg_type(ln, champ);
	void *const	val = ft_get_arg_val(ln, type, champ, begin);
	const int 	exp_arg_count = g_functions[cmd->cmd].arg_count;

	if (cmd->arg_count < exp_arg_count &&
			(cmd->arg_types[cmd->arg_count] = type))
		cmd->args[cmd->arg_count] = val;
	ft_skip_spaces(ln);
	cmd->arg_count += !((cmd->arg_count >= exp_arg_count) &&
		type == -1 * (int)T_IND && (!**ln || **ln == COMMENT_CHAR ||
		**ln == ALT_CMT_CHAR)); //fixme
	if (cmd->arg_count > 0 && cmd->arg_count <= exp_arg_count)
		ft_check_arg_type_for_op(champ, cmd, type, begin);
	if (!**ln || **ln == COMMENT_CHAR || **ln == ALT_CMT_CHAR)
		return (0);
	ft_move_to_next_arg(champ, ln);
	return (1);
}

static inline void	ft_check_arg_count(t_champ *champ, t_cmd *cmd)
{
	const int 	exp_arg_count = g_functions[cmd->cmd].arg_count;

	if (cmd->arg_count != exp_arg_count)
		ft_make_error(BAD_ARG_COUNT, champ, champ->curr_cmd->begin_pos,
			(void*[4]){g_functions[cmd->cmd].name, (void*)(size_t)exp_arg_count,
			(void*)(size_t)cmd->arg_count, 0});
}

static inline int	ft_get_op_size(t_cmd *cmd)
{
	int res;
	int i;

	i = -1;
	res = 0;
	res += 1 + g_functions[cmd->cmd].need_types_byte;
	while (++i < cmd->arg_count)
	{
		if (cmd->arg_types[i] == T_REG)
			res += 1;
		else if (cmd->arg_types[i] == T_DIR || cmd->arg_types[i] == T_LAB)
			res += g_functions[cmd->cmd].short_dir ? IND_SIZE : DIR_SIZE;
		else if (cmd->arg_types[i] == T_IND)
			res += IND_SIZE;
	}
	return (res);
}

static inline void	ft_upd_labels(t_champ *champ)
{
	int		i;
	int		to;
	void	**map_val;

	i = -1;
	to = champ->current_labels->len;
	while (++i < to)
	{
		if (champ->current_labels->data[i])
		{
			if (!(map_val = ft_map_get(champ->labels,
									   champ->current_labels->data[i])))
				exit(ft_free_champ(&champ, 666));
			*map_val = (void*)(size_t)champ->address;
		}
	}
	champ->current_labels->len = 0;
}

void 		ft_parse_command(t_champ *champ, char *ln, int cmd_num)
{
	t_cmd *cmd;

	if (!(cmd = (t_cmd*)ft_memalloc(sizeof(t_cmd))))
		exit(ft_free_champ(&champ, 666));
	champ->curr_cmd = cmd;
	cmd->cmd = (unsigned char)cmd_num;
	cmd->begin_pos = ln - champ->curr_line + 1;
	ln += g_functions[cmd_num].namelen;
	ft_skip_spaces(&ln);
	while (ft_parse_arg(champ, cmd, &ln))
		;
	ft_check_arg_count(champ, cmd);
	cmd->address = champ->address;
	if (!ft_vector_push_back(&champ->cmds, cmd) || (champ->curr_cmd = 0))
		exit(ft_free_champ(&champ, 666));
	ft_upd_labels(champ);
	champ->address += ft_get_op_size(cmd);
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
		lbl = 0;
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

	label = ft_get_lbl_name(champ, &ln,
			(char[4]){COMMENT_CHAR, LABEL_CHAR, ALT_CMT_CHAR, '\0'});
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

static inline int	ft_is_lbl(char *ln, t_champ *champ, int is_cmd, int pos)
{
	static int	name_cmd_len = -1;
	static int	comm_cmd_len = -1;
	int			cm_err;

	cm_err = 0;
	if (name_cmd_len == -1 || comm_cmd_len == -1)
	{ // todo try to use this pattern in header parsing
		name_cmd_len = ft_strlen(NAME_CMD_STRING);
		comm_cmd_len = ft_strlen(COMMENT_CMD_STRING);
	}
	if (!is_cmd)
	{
		if (!ft_strncmp(ln, NAME_CMD_STRING, name_cmd_len) ||
			(!ft_strncmp(ln, COMMENT_CMD_STRING, comm_cmd_len) && (cm_err = 1)))
		{
			ft_make_error(NM_CMD_WRONG_PLACE, champ, pos,
						  (void*[4]){!cm_err ? "name" : "comment", 0, 0, 0}); // todo retest this error
			return (0);
		}
		return (1);
	}
	while (ft_strchr(LABEL_CHARS, *ln) && *ln)
		++ln;
	ft_skip_spaces(&ln);
	return (*ln == LABEL_CHAR ? 1 : 0);
}

void 		ft_parse_line(t_champ *champ, char *ln)
{
	int	cmd;

	int is_lbl;

	is_lbl = 0;
	if (!*ln)
		return ;
	ft_skip_spaces(&ln);
	if (!*ln || *ln == COMMENT_CHAR || *ln == ALT_CMT_CHAR)
		return ;
	cmd = ft_is_command(ln);
	is_lbl = ft_is_lbl(ln, champ, cmd >= 0, ln - champ->curr_line + 1);
	if (is_lbl)
		ft_parse_label(champ, ln);
	else if (cmd >= 0)
		ft_parse_command(champ, ln, cmd);
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

	//todo throw warning about empty champ (no exec part)

	if ((fd = open(file, O_RDONLY)) == -1) // todo check extension
		return (0);
	if (!(champ = ft_make_champ(file, fd)))
		return (0);
	ft_parse_header(champ, fd);
	ft_parse_exec(champ, fd);

	return (champ);
}

