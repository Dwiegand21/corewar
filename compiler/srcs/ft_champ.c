/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_champ.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 09:07:31 by ggerardy          #+#    #+#             */
/*   Updated: 2019/05/26 09:07:31 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int 		ft_free_champ(t_champ **champ, int ret)
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

t_champ		*ft_make_champ(char *file, int fd)
{
	t_champ *champ;

	if (!(champ = (t_champ*)ft_memalloc(sizeof(t_champ))))
		return (0);
	if (!(champ->cmds = ft_make_vector_free(64, ft_free_cmd)) ||
		!(champ->name = ft_make_string(PROG_NAME_LENGTH)) ||
		!(champ->comment = ft_make_string(COMMENT_LENGTH)) ||
		!(champ->labels = ft_make_std_map(STRING, INT32_T)) ||
		!(champ->current_labels = ft_make_vector(4)))
		return ((void*)(size_t)ft_free_champ(&champ, 0));
	champ->file = file;
	champ->fd = fd;
	return (champ);
}

void 		ft_champ_upd_line(t_champ *champ, char *line)
{
	free(champ->curr_line);
	champ->curr_line = line;
}
