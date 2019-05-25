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

int 		ft_free_champ(t_champ **champ, int ret)
{
	if (!champ || !*champ)
		return (ret);
	ft_free_vector(&(*champ)->tokens);
	ft_free_string(&(*champ)->exec);
	ft_free_vector(&(*champ)->errors);
	free(*champ);
	*champ = 0;
	return (ret);
}

t_champ		*ft_make_champ(char *file)
{
	t_champ *champ;

	if (!(champ = (t_champ*)ft_memalloc(sizeof(t_champ))))
		return (0);
	if (!(champ->tokens = ft_make_vector_free(64, ft_free_vector_simple)) ||
		!(champ->exec = ft_make_string(128)) ||
		!(champ->errors = ft_make_vector_free(32, free)) ||
		!(champ->name = ft_make_string(PROG_NAME_LENGTH)) ||
		!(champ->comment = ft_make_string(COMMENT_LENGTH)))
		return ((void*)(size_t)ft_free_champ(&champ, 0));
	champ->file = file;
	return (champ);
}

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