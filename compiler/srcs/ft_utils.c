/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 19:44:09 by ggerardy          #+#    #+#             */
/*   Updated: 2019/05/25 19:44:09 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

size_t			ft_get_max_len(t_token_type type)
{
	return ((type == NAME ? PROG_NAME_LENGTH : COMMENT_LENGTH));
}

t_flags			*ft_make_flags(void)
{
	t_flags *fl;

	if (!(fl = ft_memalloc(sizeof(t_flags))))
		return (0);
	if (!(fl->srcs = ft_make_vector(8)) ||
		!(fl->outputs = ft_make_vector(8)))
		return ((void*)(size_t)fl);
	return (fl);
}

void			ft_make_error(t_error type, t_champ *champ, int pos,
		void *args[4])
{
	ft_fdprintf(2, g_is_silent ? "" : g_errors[type],
			args[0], args[1], args[2], args[3]);
	ft_fdprintf(2, g_is_silent ? "" : g_pos,
			champ->file, champ->line, pos);
	++champ->error_count;
}

unsigned int	ft_get_lbl_arg(t_champ *champ, t_cmd *cmd, int i)
{
	void			**map_val;
	unsigned int	arg;

	arg = 0;
	if (!(map_val = ft_map_get(champ->labels, cmd->args[i])))
		exit(ft_free_champ(&champ, 666));
	if (*map_val == champ->labels->nil)
		ft_make_error(UNKNOWN_LAB, champ, cmd->lbl_poses[i],
				(void*[4]){cmd->args[i], g_functions[cmd->cmd].name, 0, 0});
	else
		arg = (unsigned)((int)*map_val - cmd->address);
	return (arg);
}

void			ft_check_exist_name_cmt(t_champ *champ)
{
	if (!champ->name->offset)
	{
		ft_fdprintf(2, g_is_silent ? "" : g_missing_param,
				"name");
		ft_fdprintf(2, g_is_silent ? "" : g_pos_before,
				champ->file, champ->line, 0);
		++champ->error_count;
	}
	if (!champ->comment->offset)
	{
		ft_fdprintf(2, g_is_silent ? "" : g_missing_param,
				"comment");
		ft_fdprintf(2, g_is_silent ? "" : g_pos_before,
				champ->file, champ->line, 0);
		++champ->error_count;
	}
}
