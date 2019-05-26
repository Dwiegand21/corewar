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



void		ft_make_error(t_error type, t_champ *champ, int pos, void* args[4])
{
	ft_fdprintf(2, g_errors[type], args[0], args[1], args[2], args[3]);
	ft_fdprintf(2, g_pos, champ->file, champ->line, pos);
	++champ->error_count;
}

void		*tokenize(t_token_type type, void *carry) // fixme make `extern inline`
{
	return ((void*)((size_t)carry | ((unsigned long)type << 61u)));
}

void		ft_check_exist_name_cmt(t_champ *champ)
{
	if (!champ->name->offset)
	{
		ft_fdprintf(2, g_missing_param, "name");
		ft_fdprintf(2, g_pos_before, champ->file, champ->line, 0);
	}
	if (!champ->comment->offset)
	{
		ft_fdprintf(2, g_missing_param, "comment");
		ft_fdprintf(2, g_pos_before, champ->file, champ->line, 0);
	}
}
