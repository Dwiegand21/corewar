/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timsort_merge.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 04:42:07 by ggerardy          #+#    #+#             */
/*   Updated: 2019/08/18 04:42:07 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "virtual_machine.h"

#define TOP_ARR_SIZE stack[stack_size - 1].len
#define MID_ARR_SIZE stack[stack_size - 2].len
#define BOT_ARR_SIZE stack[stack_size - 3].len

static inline void	ft_merge_left(int *data, const t_timsort_rng lhs,
		const t_timsort_rng rhs)
{
	unsigned int		i;
	unsigned int		j;
	int					*left;
	int					*right;
	int					*buf;

	left = data + lhs.beg - 1;
	right = data + rhs.beg;
	buf = ft_memcpy(g_sort_buffer.data, left + 1, lhs.len * sizeof(int));
	i = 0;
	j = 0;
	while (i < lhs.len && j < rhs.len && ++left)
		if (*buf >= *right && ++i)
			*left = *buf++;
		else if (++j)
			*left = *right++;
	while (i++ < lhs.len && ++left)
		*left = *buf++;
	while (j++ < rhs.len && ++left)
		*left = *right++;
}

static inline void	ft_merge_right(int *data, const t_timsort_rng lhs,
		const t_timsort_rng rhs)
{
	unsigned int		i;
	unsigned int		j;
	int					*left;
	int					*right;
	int					*buf;

	left = data + lhs.beg + lhs.len - 1;
	right = data + rhs.beg + rhs.len;
	buf = (int*)ft_memcpy(g_sort_buffer.data, right - rhs.len,
			rhs.len * sizeof(int)) + rhs.len - 1;
	i = lhs.len;
	j = rhs.len;
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

void				ft_timsort_merge_if_three(t_timsort_rng *stack,
		int stack_size,
		const unsigned int *arr_sizes,
		int *data)
{
	if (arr_sizes[0] <= arr_sizes[2])
	{
		arr_sizes[0] <= arr_sizes[1] ?
		ft_merge_right(data, stack[stack_size - 1], stack[stack_size]) :
		ft_merge_left(data, stack[stack_size - 1], stack[stack_size]);
		stack[stack_size - 1].len = arr_sizes[1] + arr_sizes[0];
	}
	else
	{
		arr_sizes[2] <= arr_sizes[1] ?
		ft_merge_left(data, stack[stack_size - 2], stack[stack_size - 1]) :
		ft_merge_right(data, stack[stack_size - 2], stack[stack_size - 1]);
		stack[stack_size - 2].len = arr_sizes[2] + arr_sizes[1];
		((void**)stack)[stack_size - 1] = ((void**)stack)[stack_size];
	}
}

void				ft_merge_rest(t_timsort_rng *stack,
		int stack_size,
		unsigned int *arr_sizes,
		int *data)
{
	while (--stack_size > 0)
	{
		arr_sizes[0] = stack[stack_size].len;
		arr_sizes[1] = stack[stack_size - 1].len;
		arr_sizes[0] <= arr_sizes[1] ?
		ft_merge_right(data, stack[stack_size - 1], stack[stack_size]) :
		ft_merge_left(data, stack[stack_size - 1], stack[stack_size]);
		stack[stack_size - 1].len = arr_sizes[1] + arr_sizes[0];
	}
}

int					ft_merge_if_need(t_timsort_rng *stack,
									int stack_size,
									unsigned int *arr_sizes,
									int *data)
{
	while ((stack_size >= 3 &&
				(arr_sizes[2] = BOT_ARR_SIZE) <=
				(arr_sizes[1] = MID_ARR_SIZE) +
				(arr_sizes[0] = TOP_ARR_SIZE)) ||
			(stack_size >= 2 &&
				(arr_sizes[1] = MID_ARR_SIZE) <=
				(arr_sizes[0] = TOP_ARR_SIZE)))
	{
		if (stack_size >= 2 && arr_sizes[1] <= arr_sizes[0] && --stack_size)
		{
			ft_merge_left(data, stack[stack_size - 1], stack[stack_size]);
			stack[stack_size - 1].len = arr_sizes[1] + arr_sizes[0];
		}
		else if (stack_size >= 3 && arr_sizes[2] <= arr_sizes[1] + arr_sizes[0]
			&& --stack_size)
			ft_timsort_merge_if_three(stack, stack_size, arr_sizes, data);
	}
	return (stack_size);
}
