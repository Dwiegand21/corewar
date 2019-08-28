/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 21:38:40 by ggerardy          #+#    #+#             */
/*   Updated: 2019/08/27 21:38:40 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int					ft_is_command(char *line)
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

int					ft_get_op_size(t_cmd *cmd)
{
	int res;
	int i;

	i = -1;
	res = 0;
	res += 1 + g_functions[cmd->cmd].need_types_byte;
	while (++i < cmd->arg_count)
	{
		if (cmd->arg_types[i] & T_REG)
			res += 1;
		else if (cmd->arg_types[i] & T_DIR)
			res += g_functions[cmd->cmd].short_dir ? IND_SIZE : DIR_SIZE;
		else if (cmd->arg_types[i] & T_IND)
			res += IND_SIZE;
	}
	return (res);
}

void				ft_parse_command(t_champ *champ, char *ln, int cmd_num)
{
	t_cmd *cmd;

	if (!(cmd = (t_cmd*)ft_memalloc(sizeof(t_cmd))))
		exit(ft_free_champ(&champ, 666));
	champ->curr_cmd = cmd;
	cmd->cmd = (unsigned char)cmd_num;
	cmd->begin_pos = (int)(size_t)(ln - champ->curr_ln) + 1;
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

size_t				ft_find_bad_cmd_len(char *ln)
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
