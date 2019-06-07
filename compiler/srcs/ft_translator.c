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
	ft_bzero(buf, 33);
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
	void			**map_val;
	char 			buf[5];

	i = -1;
	while (++i < cmd->arg_count)
	{
		if (cmd->arg_types[i] == T_LAB)
			arg = ft_get_lbl_arg(champ, cmd, i);
		else if (cmd->arg_types[i] == T_)
//		if (cmd->arg_types == T_DIR)
//			arg_len = ft_int_to_bytes(buf, )
	}
}

static inline void	ft_translate_exec_part(t_champ *champ, int size_pos)
{
	int		i;
	int		to;
	t_cmd	*cmd;

	i = -1;
	to = champ->cmds->len;
	while (++i < to)
	{
		cmd = champ->cmds->data[i];
		champ->line = cmd->lbl_line;
		if (!ft_string_push_back(&champ->res, cmd->cmd) ||
			(g_functions[cmd->cmd].need_types_byte &&
			 !ft_string_push_back(&champ->res, ft_get_types_byte(cmd))))
			exit(ft_free_champ(&champ, 666));
		ft_translate_op(champ, cmd);
	}
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
	if (!champ->res)
		exit(ft_free_champ(&champ, 666));
	ft_translate_exec_part(champ, code_size_pos);
}