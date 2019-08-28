/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 21:36:20 by ggerardy          #+#    #+#             */
/*   Updated: 2019/08/27 21:36:20 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			ft_check_arg(t_champ *champ, char **ln, char *begin,
		unsigned int type)
{
	if (!(!**ln || **ln == SEPARATOR_CHAR || **ln == COMMENT_CHAR ||
		**ln == ALT_CMT_CHAR))
		return (type);
	if (type & T_DIR || type & T_REG)
		ft_make_error(MISS_ARG_AFT_PRFX, champ,
				begin - champ->curr_ln + 1,
					(void*[4]){g_nbrs[champ->curr_cmd->arg_count + 1],
					(void*)1lu, begin, g_functions[champ->curr_cmd->cmd].name});
	if (type & T_IND &&
				champ->curr_cmd->arg_count <
				g_functions[champ->curr_cmd->cmd].arg_count)
		ft_make_error(MISS_ARG, champ, begin - champ->curr_ln + 1,
					(void*[4]){g_nbrs[champ->curr_cmd->arg_count + 1],
					g_functions[champ->curr_cmd->cmd].name, 0, 0});
	return (-1 * (int)type);
}

int			ft_get_arg_type(char **ln, t_champ *champ)
{
	char *const		begin = *ln;
	unsigned int	type;

	if (**ln == DIRECT_CHAR && ++(*ln) && ft_skip_spaces(ln))
		type = T_DIR;
	else if (**ln == 'r' && ++(*ln) && ft_skip_spaces(ln))
		type = T_REG;
	else
		type = T_IND;
	if (**ln == LABEL_CHAR && ++(*ln) && ft_skip_spaces(ln))
	{
		champ->curr_cmd->lbl_line = champ->line;
		if (champ->curr_cmd->arg_count <
			g_functions[champ->curr_cmd->cmd].arg_count)
			champ->curr_cmd->lbl_poses[champ->curr_cmd->arg_count] =
					*ln - champ->curr_ln;
		type |= T_LAB;
	}
	type = (type & T_REG) ? T_REG : type;
	return (ft_check_arg(champ, ln, begin, type));
}

void		*ft_get_arg_val(char **ln, unsigned int type,
		t_champ *champ, const char *begin)
{
	void		*arg;
	char		*bad_arg;

	if ((int)type < 0)
		return (0);
	bad_arg = 0;
	arg = ((type & T_LAB) == 0) ? (void*)(size_t)ft_atoi_m(ln) :
			ft_get_lbl_name(champ, ln,
	(char[4]){COMMENT_CHAR, SEPARATOR_CHAR, ALT_CMT_CHAR, '\0'});
	if ((type & T_LAB) == 0 && **ln != SEPARATOR_CHAR && **ln != COMMENT_CHAR &&
		**ln != ALT_CMT_CHAR && **ln && !ft_isspace(**ln))
		bad_arg = *ln;
	while (!ft_isspace(**ln) && **ln != SEPARATOR_CHAR && **ln != COMMENT_CHAR
			&& **ln != ALT_CMT_CHAR && **ln)
		++(*ln);
	if (bad_arg)
		ft_make_error(BAD_ARG, champ, bad_arg - champ->curr_ln + 1,
					(void*[4]){(void*)(*ln - begin), (void*)begin, 0, 0});
	if (type & T_REG && (int)(size_t)arg < 0) // todo <=
		ft_make_error(BAD_REG_IDX, champ, begin - champ->curr_ln + 1,
					(void*[4]){(void*)(*ln - begin), (void*)begin, 0, 0});
	if (type & T_LAB && champ->curr_cmd->arg_count >=
		g_functions[champ->curr_cmd->cmd].arg_count)
		free(arg);
	return (arg);
}

void		ft_move_to_next_arg(t_champ *champ, char **ln)
{
	char	*sep;

	sep = (**ln == SEPARATOR_CHAR) ? *ln : 0;
	((*ln) += (sep != 0));
	ft_skip_spaces(ln);
	if (!sep)
		ft_make_error(MISSING_SEP, champ, *ln - champ->curr_ln + 1,
				(void*[4]){(void*)(size_t)SEPARATOR_CHAR, 0, 0, 0});
	if ((!**ln || **ln == COMMENT_CHAR || **ln == ALT_CMT_CHAR ||
		**ln == SEPARATOR_CHAR) &&
		champ->curr_cmd->arg_count >=
		g_functions[champ->curr_cmd->cmd].arg_count)
	{
		ft_make_error(EXTRA_SEP, champ, sep - champ->curr_ln + 1,
		(void *[4]) {(void *)(size_t)SEPARATOR_CHAR, 0, 0, 0});
		champ->curr_cmd->arg_count -=
				champ->curr_cmd->arg_count >
				g_functions[champ->curr_cmd->cmd].arg_count;
	}
}

void		ft_check_arg_type_for_op(t_champ *champ, t_cmd *cmd,
		unsigned int type, char *begin)
{
	if ((int)type == -1 * (int)T_IND)
		return ;
	type = ((int)type < 0) ? (int)type * -1 : type;
	if (type & g_functions[cmd->cmd].arg[cmd->arg_count - 1])
		return ;
	ft_make_error(BAD_ARG_TYPE, champ, begin - champ->curr_ln + 1,
			(void*[4]){g_nbrs[cmd->arg_count], g_functions[cmd->cmd].name,
			g_types[g_functions[cmd->cmd].arg[cmd->arg_count - 1] - 1],
			g_types[(type & ~T_LAB) - 1]});
}
