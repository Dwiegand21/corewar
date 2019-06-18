/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_processes_output.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 05:27:38 by axtazy            #+#    #+#             */
/*   Updated: 2019/06/12 13:19:01 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compare_dumps.h"

static FILE* 	open_process(char* process, char* flag, int our)
{
	char	*command = NULL;
	char 	*s;

	if ((strstr(process, "corewar")) == NULL)
		ft_error("Invalide name of file\n", __func__);
	command = ft_strjoin("./", process);
	if (command == NULL)
		ft_error("ft_strjoin: memory allocated error", __func__);
	s = command;
	command = ft_strjoin(command, " ");
	free(s);
	if (command == NULL)
		ft_error("ft_strjoin: memory allocated error", __func__);

	if (our)
		flag = ft_strjoin(" -p ", flag);

	s = command;
	command = ft_strjoin(command, flag);
	free(s);
	if (command == NULL)
		ft_error("ft_strjoin: memory allocated error", __func__);
	FILE	*p = popen(command, "r");
	if (p == NULL)
		ft_error("popen: open error", __func__);
	return (p);
}

void			print_bits(void *p, size_t size)
{
	while (size--)
	{
		for(int j = 7; j >= 0; j--)
		{
			printf("%d", ((*((char*)p) >> (size * 8 + j)) & 0x01));
		}
		printf(" ");
	}
	printf("\n");
}

static t_list*	get_process(char *buff)
{
	t_process *p = malloc(sizeof(t_process));
	if (p == NULL)
		ft_error(ERRALLOC, __func__);
	p->player = (int32_t)(buff[0] - '0');
	p->pc = ft_atoi(buff + 1);
	return (ft_lstnew(p, sizeof(t_process)));
}

static int 		data_compare(t_list *a, t_list *b)
{
	return (((t_process *)a->content)->pc - ((t_process *)b->content)->pc);
}

static t_list*	read_processes(char *buff, FILE *process)
{
	t_list* lst;

	lst = NULL;
	while ((fgets(buff, BUFF_SIZE - 1, process)) != NULL)
	{
		if ((ft_strncmp(buff, PROC_PRINT, 8)) == 0)
			break ;
		//printf("buff_data: |%s|\n", buff);
		ft_lstadd(&lst, get_process(buff));
	}
	ft_lstsort(lst, &data_compare);
	return (lst);
}

static char* 	read_process(FILE* process, t_list **processes_list)
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
		if ((strncmp(buff, PROC_PRINT, 8)) == 0)
			*processes_list = read_processes(buff, process);
	}
	pclose(process);
	if (output[0] == 0)
	{
		ft_error("Invalide output", __func__);
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

void 			data_print(t_list *a)
{
	printf("%d: %d\n", ((t_process *)a->content)->player,
							((t_process *)a->content)->pc);
}

int 			read_processes_output(t_dump *dd, char *av[])
{
	t_list *list;

	list = NULL;

	dd->origin_vm = open_process(av[2], av[3], 0);
	dd->strings->origin = read_process(dd->origin_vm, &list);
	dd->our_vm = open_process(av[1], av[3], 1);
	dd->strings->our = read_process(dd->our_vm, &list);
	dd->processes = list;
	ft_lstiter(list, &data_print);
	//printf("end\n");
	//exit(1);
	return (0);
}