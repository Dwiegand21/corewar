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

int					ft_parse_arg(t_champ *champ, t_cmd *cmd, char **ln)
{
	char *const			begin = *ln;
	const unsigned int	type = ft_get_arg_type(ln, champ);
	void *const			val = ft_get_arg_val(ln, type, champ, begin);
	const int			exp_arg_count = g_functions[cmd->cmd].arg_count;

	if (cmd->arg_count < exp_arg_count &&
			(cmd->arg_types[cmd->arg_count] = type))
		cmd->args[cmd->arg_count] = val;
	ft_skip_spaces(ln);
	cmd->arg_count += !((cmd->arg_count >= exp_arg_count) &&
			(int)type == -1 * (int)T_IND && (!**ln || **ln == COMMENT_CHAR ||
		**ln == ALT_CMT_CHAR));
	if (cmd->arg_count > 0 && cmd->arg_count <= exp_arg_count)
		ft_check_arg_type_for_op(champ, cmd, type, begin);
	if (!**ln || **ln == COMMENT_CHAR || **ln == ALT_CMT_CHAR)
		return (0);
	ft_move_to_next_arg(champ, ln);
	return (1);
}

void				ft_check_arg_count(t_champ *champ, t_cmd *cmd)
{
	const int	exp_arg_count = g_functions[cmd->cmd].arg_count;

	if (cmd->arg_count != exp_arg_count)
		ft_make_error(BAD_ARG_COUNT, champ, champ->curr_cmd->begin_pos,
			(void*[4]){g_functions[cmd->cmd].name, (void*)(size_t)exp_arg_count,
			(void*)(size_t)cmd->arg_count, 0});
}

void				ft_parse_line(t_champ *champ, char *ln)
{
	int	cmd;
	int	is_lbl;

	if (!ln || !*ln)
		return ;
	ft_skip_spaces(&ln);
	if (!*ln || *ln == COMMENT_CHAR || *ln == ALT_CMT_CHAR)
		return ;
	cmd = ft_is_command(ln);
	is_lbl = ft_is_lbl(ln, champ, cmd >= 0,
			(int)(size_t)(ln - champ->curr_ln) + 1);
	if (is_lbl)
		ft_parse_label(champ, ln);
	else if (cmd >= 0)
		ft_parse_command(champ, ln, cmd);
}

void				ft_parse_exec(t_champ *champ, int fd)
{
	char *ln;

	ft_parse_line(champ, champ->curr_ln);
	while ((ln = (void*)1lu) && ft_get_next_line(fd, &ln, BUFF_SIZE) &&
			++champ->line)
	{
		if (!ln)
			exit(ft_free_champ(&champ, 13));
		ft_champ_upd_line(champ, ln);
		ft_parse_line(champ, ln);
	}
}

t_champ				*ft_parser(char *file)
{
	t_champ	*champ;
	int		fd;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (0);
	if (!(champ = ft_make_champ(file, fd)))
		return (0);
	ft_parse_header(champ, fd);
	ft_parse_exec(champ, fd);
	ft_upd_labels(champ);
	return (champ);
}
