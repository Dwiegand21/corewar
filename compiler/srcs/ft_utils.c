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
	{
		return (ret);
	}
	ft_free_vector(&(*champ)->tokens);
	free(*champ);
	*champ = 0;
	return (ret);
}

t_champ		*ft_make_champ()
{
	t_champ *champ;

	if (!(champ = (t_champ*)ft_memalloc(sizeof(t_champ)))) {
		return (0);
	}
	return (0);
	//if (!(champ->tokens = ft_make_vector_free())) // todo try to save pointer in 7 bytes
}

extern inline void *tokenize(t_token_type type, size_t carry)
{
	return ((void*)(carry | ((unsigned long)type << 61u)));
}