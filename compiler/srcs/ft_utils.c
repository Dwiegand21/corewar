/* ************************************************************************** */
/*                                                                            */
/*                                                            ::: ::::::::    */
/*    ft_utils.c                                         :+: :+: :+:          */
/*                                                             +:+ +:+ +:+    */
/*    By: ggerardy <marvin@42.fr>                    +#+ +:+ +#+              */
/*                                                         +#+#+#+#+#+ +#+    */
/*    Created: 2019/05/24 12:02:09 by ggerardy          #+# #+#               */
/*    Updated: 2019/05/24 12:02:09 by ggerardy         ### ########.fr        */
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

t_champ		*ft_make_champ(void)
{
	t_champ *champ;

	if (!(champ = (t_champ*)ft_memalloc(sizeof(t_champ))))
		return (0);
	if (!(champ->tokens = ft_make_vector_free(64, ft_free_vector_simple)) ||
		!(champ->exec = ft_make_string(128)) ||
		!(champ->errors = ft_make_vector_free(32, free)))
		return ((void*)(size_t)ft_free_champ(&champ, 0));
	return (champ);
}

void *tokenize(t_token_type type, void *carry) // fixme make `extern inline`
{
	return ((void*)((size_t)carry | ((unsigned long)type << 61u)));
}