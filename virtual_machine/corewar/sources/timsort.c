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

#define TOP_ARR_SIZE stack[stack_size - 1][1]
#define MID_ARR_SIZE stack[stack_size - 2][1]
#define BOT_ARR_SIZE stack[stack_size - 3][1]

static inline unsigned int	ft_get_minrun(size_t len)
{
	unsigned char flag = 0;
	while (len >= 64)
	{
		flag |= len & 1u;
		len >>= 1u;
	}
	return (len + flag);
}

static inline void	ft_reverse_subarray(int *data, unsigned int len)
{
	unsigned int i;
	const unsigned int go_to = len / 2;
	int tmp;

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

static inline void	ft_insertion_sort(register int *data, register unsigned int len)
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

static inline void	ft_merge_left(int *data, unsigned int lhs[2], unsigned int rhs[2])
{
	const unsigned int	zl = lhs[1];
	const unsigned int	zr = rhs[1];
	unsigned int 		i;
	unsigned int 		j;
	int 				*left;
	int 				*right;
	int 				*buf;

	left = data + lhs[0] - 1;
	right = data + rhs[0];
	buf = ft_memcpy(g_buffer->data, left + 1, zl * sizeof(int));
	i = 0;
	j = 0;
	while (i < zl && j < zr && ++left)
		if (*buf >= *right && ++i)
			*left = *buf++;
		else if (++j)
			*left = *right++;
	while (i++ < zl && ++left)
		*left = *buf++;
	while (j++ < zr && ++left)
		*left = *right++;
}

static inline void	ft_merge_right(int *data, unsigned int lhs[2], unsigned int rhs[2])
{
	const unsigned int	zl = lhs[1];
	const unsigned int	zr = rhs[1];
	unsigned int 		i;
	unsigned int 		j;
	int 				*left;
	int 				*right;
	int 				*buf;

	left = data + lhs[0] + zl - 1;
	right = data + rhs[0] + zr;
	buf = (int*)ft_memcpy(g_buffer->data, right - zr, zr * sizeof(int)) + zr - 1;
	i = zl;
	j = zr;
	while (i > 0 && j > 0 && --right)
		if (*buf < *left && j--)
			*right = *buf--;
		else if (i--)
			*right = *left--;
	while (j-- > 0 && --right)
		*right = *buf--;
	while (i-- > 0 && --right)
		*right = *left--;
}

// todo change fucking defines to variables
void	ft_timsort_split_and_merge(int *data, size_t len, unsigned int minrun, int *const array_end)
{
	unsigned int	end;
	unsigned int	stack[len / minrun + 1][2];
	int 			stack_size;
	unsigned int	top_arr_size;
	unsigned int	mid_arr_size;
	unsigned int	bot_arr_size;

	end = 0;
	stack_size = 0;
	ft_bzero(stack, (len / minrun + 1) * 2 * sizeof(int));
	while (end < len)
	{
		stack[stack_size][0] = end;
		stack[stack_size][1] = (data == array_end) ? 1u : ft_find_subarray_len(data + end + 1, minrun, array_end);
		end += stack[stack_size++][1];

		while((stack_size >= 3 &&
			(bot_arr_size = BOT_ARR_SIZE) <= (mid_arr_size = MID_ARR_SIZE) +
				(top_arr_size = TOP_ARR_SIZE)) ||
			(stack_size >= 2 &&
			(mid_arr_size = MID_ARR_SIZE) <= (top_arr_size = TOP_ARR_SIZE)))
		{
			if (stack_size >= 2 && mid_arr_size <= top_arr_size && --stack_size)
			{
				ft_merge_left(data, stack[stack_size - 1], stack[stack_size]);
				stack[stack_size - 1][1] = mid_arr_size + top_arr_size;
			}
			else if (stack_size >= 3 && bot_arr_size <= mid_arr_size + top_arr_size && --stack_size)
			{
				if (top_arr_size <= bot_arr_size)
				{
					top_arr_size <= mid_arr_size ?
					ft_merge_right(data, stack[stack_size - 1], stack[stack_size]) :
					ft_merge_left(data, stack[stack_size - 1], stack[stack_size]);
					stack[stack_size - 1][1] = mid_arr_size + top_arr_size;
				}
				else
				{
					bot_arr_size <= mid_arr_size ?
					ft_merge_left(data, stack[stack_size - 2], stack[stack_size - 1]) :
					ft_merge_right(data, stack[stack_size - 2], stack[stack_size - 1]);
					stack[stack_size - 2][1] = bot_arr_size + mid_arr_size;
					((void**)stack)[stack_size - 1] = ((void**)stack)[stack_size];
				}
			}
		}
	}
	while (--stack_size > 0)
	{
		(top_arr_size = stack[stack_size][1]) <= (mid_arr_size = stack[stack_size - 1][1]) ?
		ft_merge_right(data, stack[stack_size - 1], stack[stack_size]) :
		ft_merge_left(data, stack[stack_size - 1], stack[stack_size]);
		stack[stack_size - 1][1] = mid_arr_size + top_arr_size;
	}
}

void	ft_timsort_int(int *data, int len)
{
	const unsigned int		minrun = ft_get_minrun(len);
	int *const				array_end = data + len;

	while (g_buffer->capacity < len)
		ft_vm_vector_int_realloc(g_buffer); // todo protect ??

	if (len <= 64)
	{
		return (ft_insertion_sort(data, len));
	}
	ft_timsort_split_and_merge(data, len, minrun, array_end);
}
