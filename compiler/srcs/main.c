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
//	ft_printf("%#llB\n", p);
//
//	ft_printf("%#llB\n", GET_DATA(p));
//	ft_printf("%#hhB\n", GET_TYPE(p));

	if (ac != 2)
		return (0);

	t_champ	*champ;

	champ = ft_parser(av[1]); // todo too big champ error
	ft_translate_to_bytecode(champ);


	int fd = open("master_of_puppets.refcor", O_RDONLY);
	char *ref = malloc(10000);
	ft_get_next_line(fd, &ref, 10000);
	char *my = champ->res->data;
	int i = 0;
	while (i < 1000)
	{
		ft_printf("Different chars ref:%#5.1r my:%#5.1r in pos %5d |%c\n",
				ref, my, i++, *ref == *my ? '+' : '-');
		ref++;
		my++;
	}

	//write(1, champ->res->data, champ->res->len);

	ft_free_champ(&champ, 0);



	//printf("<%c>%d\n%s", c, c,BACKSLASH_LITERALS);


	return 0;
}