/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_print_dump.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 10:09:39 by dwiegand          #+#    #+#             */
/*   Updated: 2019/06/13 21:54:50 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"
#include <stdlib.h>

void			print_bits(void *p, size_t size)
{
	while (size--)
	{
		for (int j = 7; j >= 0; j--)
		{
			printf("%d", ((*((char*)p) >> (size * 8 + j)) & 0x01));
		}
		printf(" ");
	}
	printf("\n");
}

static void		print_hex_addr(int32_t index)
{
	int32_t		i;
	char 		c;

	write(1, "0x", 2);
	i = 0;
	while (i < 4)
	{
		c = ((index & 0xf000) >> 12);
		if (c < 10)
			ft_putchar(c + '0');
		else
			ft_putchar(c % 10 + 'a');
		i++;
		index <<= 4;
	}
	write(1, " :", 2);
}

static void		char_to_hex(uint8_t c)
{
	if (((c >> 4) & 0x0f) < 10)
		ft_putchar(((c & 0xf0) >> 4) + '0');
	else
		ft_putchar(((c & 0xf0) >> 4) % 10 + 'a');
	if ((c & 0x0f) < 10)
		ft_putchar(((c & 0x0f)) + '0');
	else
		ft_putchar(((c & 0x0f)) % 10 + 'a');
}

static void		print_processes(t_list *processes)
{
	if (DUMP_CMP == 0)
		return ;
	ft_putendl(PROC_PRINT);
	while (processes != NULL)
	{
		ft_putnbr(((t_process *)processes->content)->player);
		ft_putnbr(((t_process *)processes->content)->pc);
		ft_putendl("");
		processes = processes->next;
	}
	ft_putendl(PROC_PRINT);
}

void			print_dump(t_area *area)
{
	int32_t		i;
	int32_t		j;

	i = 0;
	while (i < 64)
	{
		print_hex_addr(i * 64);
		j = 0;
		while (j < 64)
		{
			write(1, " ", 1);
			char_to_hex(MAP[i * 64 + j]);
			j++;
		}
		write(1, " \n", 2);
		i++;
	}
	exit(1);
	//print_processes(area->processes);
}