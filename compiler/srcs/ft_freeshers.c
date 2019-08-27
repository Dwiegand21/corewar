/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freeshers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 21:07:29 by ggerardy          #+#    #+#             */
/*   Updated: 2019/08/27 21:07:29 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			ft_free_champ(t_champ **champ, int ret)
{
	if (!champ || !*champ)
		return (ret);
	ft_free_vector(&(*champ)->cmds);
	ft_free_vector(&(*champ)->current_labels);
	ft_free_string(&(*champ)->comment);
	ft_free_string(&(*champ)->name);
	ft_free_string(&(*champ)->res);
	free((*champ)->curr_line);
	ft_free_cmd((*champ)->curr_cmd);
	ft_free_map(&(*champ)->labels);
	ft_get_next_line((*champ)->fd, 0, -1);
	free(*champ);
	*champ = 0;
	return (ret);
}

void		ft_free_cmd(void *p)
{
	t_cmd	*cmd;
	int		i;

	if (!p)
		return ;
	i = -1;
	cmd = p;
	while (++i < 3)
	{
		if (cmd->arg_types[i] & T_LAB)
		{
			free(cmd->args[i]);
		}
	}
	free(cmd);
}

int			ft_free_flags(t_flags *fl, int ret)
{
	if (!fl)
		return (ret);
	ft_free_vector(&fl->srcs);
	ft_free_vector(&fl->outputs);
	free(fl);
	return (ret);
}
