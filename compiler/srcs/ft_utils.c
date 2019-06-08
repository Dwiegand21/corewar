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

void ft_free_cmd(void *p)
{
	t_cmd *cmd;
	int i;

	if (!p)
		return ;
	i = -1;
	cmd = p;
	while (++i < 3)
	{
		if (cmd->arg_types[i] == T_LAB)
		{
			free(cmd->args[i]);
		}
	}
	free(cmd);
}

void		ft_make_error(t_error type, t_champ *champ, int pos, void *args[4])
{
	ft_fdprintf(2, g_errors[type], args[0], args[1], args[2], args[3]);
	ft_fdprintf(2, g_pos, champ->file, champ->line, pos);
	++champ->error_count;
}

void		*tokenize(t_token_type type, void *carry) // fixme make `extern inline`
{
	return ((void*)((size_t)carry | ((unsigned long)type << 61u)));
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

void		ft_check_exist_name_cmt(t_champ *champ)
{
	if (!champ->name->offset)
	{ // todo use ft_make_error
		ft_fdprintf(2, g_missing_param, "name");
		ft_fdprintf(2, g_pos_before, champ->file, champ->line, 0);
		++champ->error_count;
	}
	if (!champ->comment->offset)
	{ // todo use ft_make_error
		ft_fdprintf(2, g_missing_param, "comment");
		ft_fdprintf(2, g_pos_before, champ->file, champ->line, 0);
		++champ->error_count;
	}
}
