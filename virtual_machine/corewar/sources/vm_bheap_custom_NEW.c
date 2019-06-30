/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bheap_custom.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 17:13:50 by dwiegand          #+#    #+#             */
/*   Updated: 2019/06/30 17:22:30 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"
#include "./../../libft/sources/ft_vector/ft_vector_assets.h"
#include "./../../libft/sources/ft_binary_heap/ft_binary_heap_assets.h"

int32_t			init_process_sleep(t_process *process, u_char byte)
{
	if (byte > 0 && byte < 17)
	{
		process->f = g_ops[byte].f;
		return (g_ops[byte].sleep);
	}
	else
	{
		process->f = NULL;
		return (1);
	}
}

int32_t			run_process(t_area *area, t_pair *process)
{
	SN_CYCLES = process->key;
	process->value->f(area, process->value);
	//process->key = init_process_sleep(process->value, process->value->)
}