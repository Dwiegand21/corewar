/* ************************************************************************** */
/*                                                                            */
/*                                                            ::: ::::::::    */
/*    main.c                                             :+: :+: :+:          */
/*                                                             +:+ +:+ +:+    */
/*    By: ggerardy <marvin@42.fr>                    +#+ +:+ +#+              */
/*                                                         +#+#+#+#+#+ +#+    */
/*    Created: 2019/05/24 09:11:53 by ggerardy          #+# #+#               */
/*    Updated: 2019/05/24 09:11:53 by ggerardy         ### ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int main()
{

	void *ptr = ft_memalloc(100);
	t_token_type type = A;


	ft_printf("%#llB\n", ptr);

	size_t p = (size_t)ptr | ((unsigned long)type << 61u);

	ft_printf("%#llB\n", p);

	ft_printf("%#llB\n", (p << 3u) >> 3u);
	ft_printf("%#llB\n", p >> 61u);

	return 0;
}