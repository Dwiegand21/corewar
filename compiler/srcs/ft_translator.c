/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_translator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 05:55:38 by ggerardy          #+#    #+#             */
/*   Updated: 2019/06/07 05:55:38 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static inline char	*ft_int_to_bytes(char buf[5], unsigned int n, int len)
{
	int i;

	i = 0;
	ft_bzero(buf, 4);
	while (++i <= len)
	{
		buf[i] = (char)n;
		n >>= 8u;
	}
	return (buf);
}

static inline char ft_get_types_byte(t_cmd *cmd)
{
	unsigned char	res;
	unsigned char	code;
	int				i;
	i = -1;
	res = 0;
	while (++i < 4)
	{
		code = 0;
		if (i < cmd->arg_count)
		{
			if (cmd->arg_types[i] == T_REG)
				code = REG_CODE % 4;
			else if (cmd->arg_types[i] == T_DIR || cmd->arg_types[i] == T_LAB)
				code = DIR_CODE % 4;
			else if (cmd->arg_types[i] == T_IND)
				code = IND_CODE % 4;
		}
		res |= code;
		res <<= 2u;
	}
	return (res);
}

static inline void	ft_translate_op(t_champ *champ, t_cmd *cmd)
{
	int				i;
	int				arg_len;
	unsigned int	arg;
	char 			buf[5];
	unsigned char	type_backup;

	i = -1;
	while (++i < cmd->arg_count)
	{
		type_backup = cmd->arg_types[i];
		if (cmd->arg_types[i] == T_LAB)
			arg = ft_get_lbl_arg(champ, cmd, i);
		else
			arg = (unsigned)cmd->args[i];
		if (cmd->arg_types[i] == T_REG)
			arg_len = 1;
		else if (cmd->arg_types[i] == T_IND ||
			(g_functions[cmd->cmd].short_dir && cmd->arg_types[i] == T_DIR))
			arg_len = IND_SIZE;
		else
			arg_len = DIR_SIZE;
		ft_string_push_back_mem(&champ->res,
				ft_int_to_bytes(buf, arg, arg_len), arg_len);
		cmd->arg_types[i] = type_backup;
	}
}

static inline void	ft_translate_exec_part(t_champ *champ, int size_pos)
{
	int		i;
	int		to;
	t_cmd	*cmd;
	char 	buf[5];

	i = -1;
	to = champ->cmds->len;
	while (++i < to)
	{
		cmd = champ->cmds->data[i];
		champ->line = cmd->lbl_line;
		ft_string_push_back(&champ->res, cmd->cmd);
		if (g_functions[cmd->cmd].need_types_byte)
			ft_string_push_back(&champ->res, ft_get_types_byte(cmd));
		ft_translate_op(champ, cmd);
	}
	ft_memcpy(champ->res->data, ft_int_to_bytes(buf, champ->address, 4), 4); //fixme pos
}

void				ft_translate_to_bytecode(t_champ *champ)
{
	char		buf[5];
	const int 	header_size = PROG_NAME_LENGTH + COMMENT_LENGTH + 4 + 4;
	const int 	padding_size =
			((int)(header_size / 16. + 0.5) - header_size) / 2;
	const int 	code_size_pos = 4 + PROG_NAME_LENGTH + padding_size;

	if (champ->error_count)
		return ;
	champ->res = ft_make_string(4096);
	ft_string_push_back_mem(&champ->res,
			ft_int_to_bytes(buf, COREWAR_EXEC_MAGIC, 4), 4);
	ft_string_push_back_s(&champ->res, champ->name->data);
	ft_string_push_back_n_c(&champ->res,
			PROG_NAME_LENGTH - champ->name->len + padding_size + 4, '\0');
	ft_string_push_back_s(&champ->res, champ->comment->data);
	ft_string_push_back_n_c(&champ->res,
			COMMENT_LENGTH - champ->comment->len + padding_size, '\0');
	ft_translate_exec_part(champ, code_size_pos);
	if (!champ->res)
		exit(ft_free_champ(&champ, 666));
}