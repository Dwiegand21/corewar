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

#include <stdio.h> // todo delete
#include "asm.h"

int main(int ac, char **av)
{

//	void *ptr = ft_memalloc(100);
//	t_token_type type = D;
//
//
//	ft_printf("%#llB\n", ptr);
//
//	size_t p = (size_t)tokenize(type, ptr);
//
//	ft_printf("%#B\n", 84);
//	ft_printf("%#B\n\n\n", 80);
//
//	ft_printf("%#llB\n", GET_DATA(p));
//	ft_printf("%#hhB\n", GET_TYPE(p));

	if (ac != 2)
		return (0);

	t_champ	*champ;

	champ = ft_parser(av[1]); // todo too big champ error
	ft_translate_to_bytecode(champ);


	int fd = open("gg.test.cor", O_RDONLY);
	char *ln;
	int res;
	t_string *ref = ft_gnl_bin(fd, &ln, 10000, &res);
	t_string *my = champ->res;
	size_t i = 0;
	while (i < my->len && i < ref->len)
	{
		ft_printf("Different chars ref:{Yellow}%5d{eof} my:{Yellow}%5d{eof} in pos %5d |%c\n",
			ref->data[i], my->data[i], i, ref->data[i] == my->data[i] ? '+' : '-');
		i++;
	}
	if (i == ref->len)
		ft_printf("{Red}Ref ended{eof}\n");
	if (i == my->len)
		ft_printf("{Red}My ended{eof}\n");

	//write(1, champ->res->data, champ->res->len);

	ft_free_champ(&champ, 0);



	//printf("<%c>%d\n%s", c, c,BACKSLASH_LITERALS);


	return 0;
}