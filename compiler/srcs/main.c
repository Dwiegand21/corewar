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

t_string *ft_readall(char *name)
{
	/* declare a file pointer */
	FILE    *infile;
	char    *buffer;
	long    numbytes;
	t_string *res = ft_make_string(10);

/* open an existing file for reading */
	infile = fopen(name, "r");

/* quit if the file does not exist */
	if(infile == NULL)
		return 0;

/* Get the number of bytes */
	fseek(infile, 0L, SEEK_END);
	numbytes = ftell(infile);

/* reset the file position indicator to
the beginning of the file */
	fseek(infile, 0L, SEEK_SET);

/* grab sufficient memory for the
buffer to hold the text */
	buffer = (char*)calloc(numbytes, sizeof(char));

/* memory error */
	if(buffer == NULL)
		return 0;

/* copy all the text into the buffer */
	fread(buffer, sizeof(char), numbytes, infile);
	fclose(infile);

	res->data = buffer;
	res->len = numbytes;
	return (res);
}


int		main(int ac, char **av)
{
//	t_flags	*fl;
//
//	if (!(fl = ft_find_s_h_flags(ac, (const char *const *)av)))
//		exit(1);
//	ft_parse_flags(fl, ac, av);
//	ft_compile_all(fl);
//	ft_free_flags(fl, 0);


	t_champ	*champ;

	champ = ft_parser("echo2.s");
	ft_translate_to_bytecode(champ);

	t_string *ref = ft_readall("echo2.cor");
	t_string *my = champ->res;
	size_t i = 0;
	while (i < my->len && i < ref->len)
	{
		ft_printf("Different chars ref:{Yellow}%.2x{eof} my:{Yellow}%.2x{eof} in pos %5d |%s\n",
				  (u_char)ref->data[i], (u_char)my->data[i], i,
			ref->data[i] == my->data[i] ?
			"\x1B[32m+\x1B[0m" : "\x1B[1m\x1B[31m-\x1B[0m err");
		i++;
	}
	if (i == ref->len)
		ft_printf("{Red}Ref ended{eof}\n");
	if (i == my->len)
		ft_printf("{Red}My ended{eof}\n");


	return (0);
}
