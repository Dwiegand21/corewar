/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timsort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 16:00:15 by ggerardy          #+#    #+#             */
/*   Updated: 2019/08/11 16:00:15 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "virtual_machine.h"
#include "vm_vector.h"
#include "timsort.h"

static inline void			ft_reverse_subarray(int *data, unsigned int len)
{
	unsigned int		i;
	const unsigned int	go_to = len / 2;
	int					tmp;

	i = 0;
	--len;
	while (i < go_to)
	{
		tmp = data[i];
		data[i] = data[len - i];
		data[len - i] = tmp;
		++i;
	}
}

static inline void			ft_insertion_sort(register int *data,
		register unsigned int len)
{
	register int i;
	register int j;
	register int curr;

	i = 0;
	while (++i < len)
	{
		curr = data[i];
		j = i;
		while (j > 0 && data[j - 1] < curr)
		{
			data[j] = data[j - 1];
			--j;
		}
		data[j] = curr;
	}
}

static inline unsigned int	ft_find_subarray_len(int *data, unsigned int minrun,
		const int *array_end)
{
	unsigned int		len;
	const unsigned int	reverse = (data[-1] >= *data ? 0 : 1);
	int *const			start = data - 1;

	len = 1;
	while (data < array_end && ((data[-1] >= *data) ^ reverse))
	{
		++data;
		++len;
	}
	if (reverse)
		ft_reverse_subarray(start, len);
	if (len < minrun)
	{
		len = array_end - start >= minrun ? minrun : array_end - start;
		ft_insertion_sort(start, len);
	}
	return (len);
}

void						ft_timsort_split_and_merge(int *data, size_t len,
		unsigned int minrun, int *const array_end)
{
	unsigned int	end;
	unsigned int	stack[len / minrun + 1][2];
	int				stack_size;
	unsigned int	arr_sizes[3];

	end = 0;
	stack_size = 0;
	ft_bzero(stack, (len / minrun + 1) * 2 * sizeof(int));
	while (end < len)
	{
		stack[stack_size][0] = end;
		stack[stack_size][1] = (data == array_end) ? 1u :
				ft_find_subarray_len(data + end + 1, minrun, array_end);
		end += stack[stack_size++][1];
		ft_merge_if_need(stack, stack_size, arr_sizes, data);
	}
	ft_merge_rest(stack, stack_size, arr_sizes, data);
}

void						ft_timsort_int(int *data, unsigned int len)
{
	unsigned int			minrun;
	unsigned char			minrun_flag;
	int *const				array_end = data + len;

	if (len <= 64)
		return (ft_insertion_sort(data, len));
	minrun_flag = 0;
	while (len >= 64)
	{
		minrun_flag |= len & 1u;
		len >>= 1u;
	}
	minrun = len + minrun_flag;
	while (g_buffer->capacity < len)
		ft_vm_vector_int_realloc(g_buffer);
	ft_timsort_split_and_merge(data, len, minrun, array_end);
}
