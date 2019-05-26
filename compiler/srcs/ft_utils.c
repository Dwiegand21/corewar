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
	char		*res;
	char		*err;
	char		*pos_str;

	err = 0;
	pos_str = 0;
	ft_sprintf(&err, g_errors[type], args[0], args[1], args[2], args[3]);
	ft_sprintf(&pos_str, g_pos, champ->file, champ->line, pos);
	if (!err || !pos_str || !(res = ft_strjoin(err, pos_str)))
		exit(ft_free_champ(&champ, 666) +
			free_ret(err, 0) + free_ret(pos_str, 0));
	if (!ft_vector_push_back(&champ->errors, res))
		exit(ft_free_champ(&champ, 666) +
			 free_ret(err, 0) + free_ret(pos_str, 0) + free_ret(res, 0));
	free(err);
	free(pos_str);
}

void *tokenize(t_token_type type, void *carry) // fixme make `extern inline`
{
	return ((void*)((size_t)carry | ((unsigned long)type << 61u)));
}