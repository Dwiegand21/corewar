/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_print_dump.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 10:09:39 by dwiegand          #+#    #+#             */
/*   Updated: 2019/08/29 20:36:15 by dwiegand         ###   ########.fr       */
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

void				print_dump(t_area *area)
{
	int32_t		i;
	int32_t		j;

	if (is_endgame(area, 0))
		return (winner(area));
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
}
