/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_processes_output.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 05:27:38 by axtazy            #+#    #+#             */
/*   Updated: 2019/06/07 16:22:59 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compare_dumps.h"

static FILE* 	open_process(char* process, char* flag)
{
	char	*command = NULL;
	char 	*s;

	if ((strstr(process, "corewar")) == NULL)
		ft_error("Invalide name of file\n");
	command = ft_strjoin("./", process);
	if (command == NULL)
		ft_error("ft_strjoin: memory allocated error");
	s = command;
	command = ft_strjoin(command, " ");
	free(s);
	if (command == NULL)
		ft_error("ft_strjoin: memory allocated error");
	s = command;
	command = ft_strjoin(command, flag);
	free(s);
	if (command == NULL)
		ft_error("ft_strjoin: memory allocated error");
	FILE	*p = popen(command, "r");
	if (p == NULL)
		ft_error("popen: open error");
	printf("open process: OK!\n");
	return (p);
}

typedef struct		s_test
{
	uint32_t	a;
	uint32_t	b;
}					t_test;

static void 	test()
{
	write(1 , ">>OK!\n", 6);
}

static char* 	read_process(FILE* process)
{
	char 	buff[BUFF_SIZE];
	char* 	helper;
	char* 	output;

	helper = NULL;
	output = strdup("");
	while ((fgets(buff, BUFF_SIZE - 1, process)) != NULL)
	{
		if (strncmp(buff, "0x", 2) == 0)
		{
			helper = output;
			output = ft_strjoin(helper, buff);
			free(helper);

		}
		if ((strncmp(buff, PROC_PRINT, 4)) == 0)
			test();
	}
	pclose(process);
	if (output[0] == 0)
	{
		ft_error("Invalide output");
	}
	return (output);
}

//static int		is_nbr(char *str)
//{
//	while (*str != 0)
//	{
//		if (!(*str > 47 && *str < 58))
//			return (0);
//		str++;
//	}
//	return (1);
//}

int 			read_processes_output(t_dump *dd, char *av[])
{
	//if (!is_nbr(av[3]))
	//{
	//	ft_error("Invalide argument (3)");
	//}
	dd->origin_vm = open_process(av[1], av[3]);
	dd->strings->origin = read_process(dd->origin_vm);
	dd->our_vm = open_process(av[2], av[3]);
	dd->strings->our = read_process(dd->our_vm);
	return (0);
}