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

int ft_compile(char *name)
{
	t_champ	*champ;
	champ = ft_parser(name); // todo too big champ error
	ft_translate_to_bytecode(champ);
	if (champ->error_count)
		return (0);
	char *new_name = ft_upd_name(name, "cor");
	int fd = open(new_name, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	write(fd, champ->res->data, champ->res->len);
	ft_free_champ(&champ, 0);
	ft_printf("compiled %s \n", name);
	return (1);
}

static inline int	ft_ask(char *que, char *param)
{
	char b;
	ft_fdprintf(2, que, param);
	read(0, &b, 1);
	ft_printf("<%c>\n", b);
	return (1);
}

int main(int ac, char **av)
{
	//if (ac != 2)
	//	return (0);

//	int i = 0;
//	av = 0;
	ac = 0;

	//ft_ask("FF%s", "gg");


	ft_compile(av[1]);

//	while (g_names[i][0])
//	{
//		ft_compile(g_names[i]);
//		++i;
//	}

//	t_string *ref = ft_readall(new_name);
//	t_string *my = champ->res;
//	size_t i = 0;
//	while (i < my->len && i < ref->len)
//	{
//		ft_printf("Different chars ref:{Yellow}%.2x{eof} my:{Yellow}%.2x{eof} in pos %5d |%s\n",
//				  (u_char)ref->data[i], (u_char)my->data[i], i,
//			ref->data[i] == my->data[i] ?
//			"\x1B[32m+\x1B[0m" : "\x1B[1m\x1B[31m-\x1B[0m err");
//		i++;
//	}
//	if (i == ref->len)
//		ft_printf("{Red}Ref ended{eof}\n");
//	if (i == my->len)
//		ft_printf("{Red}My ended{eof}\n");



	return 0;
}