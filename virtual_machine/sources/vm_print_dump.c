/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_print_dump.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 10:09:39 by dwiegand          #+#    #+#             */
/*   Updated: 2019/08/29 16:26:06 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"
#include <stdlib.h>

static inline void	print_hex_addr(int32_t index)
{
	int32_t		i;
	char		c;

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

static inline void	char_to_hex(uint8_t c)
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

static inline int	is_endgame(t_area *area, t_process *curr)
{
	int				i;
	int				j;
	int				*data;
	int				len;
	t_vm_vector_int	*v;

	i = -1;
	while (++i < TIMELINE_SIZE && (j = -1))
	{
		v = &area->time[i];
		data = v->data;
		len = v->len;
		while (++j < len && (curr = &area->carriages->data[data[j]]))
		{
			if (curr->n_lives >= area->n_die_cycle)
				return (0);
		}
	}
	return (1);
}

int *g_prcs;
int g_prcs_count;

void		set_prcs(t_area *area)
{
	int k = 0;
	int i = -1;
	while (++i < TIMELINE_SIZE)
	{
		for (int e = 0; e < area->time[i].len; ++e)
		{
			g_prcs[k++] =  area->carriages->data[area->time[i].data[e]].pc;
		}
	}
	g_prcs_count = k;
	ft_timsort_int(g_prcs, k);
//	for (int e = k - 1; e >= 0; --e)
//	{
//		printf("%d ", g_prcs[e]);
//	}
//	printf("\n");
}

void				print_dump(t_area *area)
{
	int32_t		i;
	int32_t		j;


	g_prcs = ft_memalloc(sizeof(int) * 1000000 * 5);
	set_prcs(area);
	int k = g_prcs_count - 1;

	if (is_endgame(area, 0))
		return (winner(area));
	i = 0;
//	printf("AAAAAAA %d BBBB %d%d%d%d\n", k,
//			(g_prcs[0] == 772),
//			(g_prcs[1] == 464),
//			(g_prcs[2] == 464),
//			(g_prcs[3] == 151));
	while (i < 64)
	{
		print_hex_addr(i * 64);
		j = 0;
		while (j < 64)
		{
			write(1, " ", 1);
			if (k >= 0 && g_prcs[k] == (i * 64 + j))
			{
				//write(1, "|", 1);
				write(1, "\033[91m", 5);
			}
			char_to_hex(MAP[i * 64 + j]);
			if (k >= 0 && g_prcs[k] == (i * 64 + j))
			{
				//write(1, "|", 1);
				while (g_prcs[k] == (i * 64 + j))
					--k;
				write(1, "\033[0m", 4);
			}
			j++;
		}
		write(1, " \n", 2); // todo fucking space
		i++;
	}
}
