/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 19:43:38 by ggerardy          #+#    #+#             */
/*   Updated: 2019/05/25 19:43:38 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int main()
{

//	void *ptr = ft_memalloc(100);
//	t_token_type type = D;
//
//
//	ft_printf("%#llB\n", ptr);
//
//	size_t p = (size_t)tokenize(type, ptr);
//
//	ft_printf("%#llB\n", p);
//
//	ft_printf("%#llB\n", GET_DATA(p));
//	ft_printf("%#hhB\n", GET_TYPE(p));

	t_champ	*champ;

	champ = ft_parser("gg.test.s");

	ft_free_champ(&champ, 0);

	//printf("<%c>%d\n%s", c, c,BACKSLASH_LITERALS);


	return 0;
}