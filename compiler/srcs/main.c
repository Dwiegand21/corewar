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

char *ft_upd_name(char *name, char *postfix)
{
	int len = ft_strlen(name);
	name[len - 1] = '\0';
	return (ft_strjoin(name, postfix));
}

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

	if (champ->error_count)
		return (0);

//	int fd = open("toto.cor", O_RDONLY);
//	char *ln;
//	int res;
//	t_string *ref;
//	t_string *my = champ->res;
//	size_t i = 0;
//
//	while (i < my->len)
//	{
//		ref = ft_gnl_bin(fd, &ln, 10000, &res);
//		if (!res)
//		{
//			ft_printf("{Blue}Ref ended{eof}\n");
//			return (0);
//		}
//		ft_string_push_back(&ref, '\n');
//		size_t j = 0;
//		while (j < ref->len)
//		{
//			ft_printf("Different chars ref:{Yellow}%5d{eof} my:{Yellow}%5d{eof} in pos %5d |%c\n",
//					  ref->data[i], my->data[i], i, ref->data[i] == my->data[i] ? '+' : '-');
//			++j;
//			++i;
//		}
//		ft_printf("{Red}Ref ended{eof}\n");
//	}
//	ft_printf("{Red}My ended{eof}\n");


	char *new_name = ft_upd_name(av[1], "mycor");
	char *last_slash = ft_rstrchr(new_name, '/');
	new_name = last_slash + 1;


	int fd = open(ft_strjoin("tests/", new_name), O_CREAT | O_TRUNC | O_WRONLY, 0666);

//	t_string *ref = ft_readall("master_of_puppets.cor");
//	t_string *my = champ->res;
//	size_t i = 0;
//	while (i < my->len && i < ref->len)
//	{
//		ft_printf("Different chars ref:{Yellow}%5d{eof} my:{Yellow}%5d{eof} in pos %5d |%c\n",
//			ref->data[i], my->data[i], i, ref->data[i] == my->data[i] ? '+' : '-');
//		i++;
//	}
//	if (i == ref->len)
//		ft_printf("{Red}Ref ended{eof}\n");
//	if (i == my->len)
//		ft_printf("{Red}My ended{eof}\n");

	write(fd, champ->res->data, champ->res->len);

	ft_free_champ(&champ, 0);



	//printf("<%c>%d\n%s", c, c,BACKSLASH_LITERALS);


	return 0;
}