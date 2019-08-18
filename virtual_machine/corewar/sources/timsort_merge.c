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

#define TOP_ARR_SIZE stack[stack_size - 1][1]
#define MID_ARR_SIZE stack[stack_size - 2][1]
#define BOT_ARR_SIZE stack[stack_size - 3][1]

void			ft_merge_left(int *data, const unsigned int lhs[2],
		const unsigned int rhs[2])
{
	unsigned int		i;
	unsigned int		j;
	int					*left;
	int					*right;
	int					*buf;

	left = data + lhs[0] - 1;
	right = data + rhs[0];
	buf = ft_memcpy(g_sort_buffer->data, left + 1, lhs[1] * sizeof(int));
	i = 0;
	j = 0;
	while (i < lhs[1] && j < rhs[1] && ++left)
		if (*buf >= *right && ++i)
			*left = *buf++;
		else if (++j)
			*left = *right++;
	while (i++ < lhs[1] && ++left)
		*left = *buf++;
	while (j++ < rhs[1] && ++left)
		*left = *right++;
}

void			ft_merge_right(int *data, const unsigned int lhs[2],
		const unsigned int rhs[2])
{
	unsigned int		i;
	unsigned int		j;
	int					*left;
	int					*right;
	int					*buf;

	left = data + lhs[0] + lhs[1] - 1;
	right = data + rhs[0] + rhs[1];
	buf = (int*)ft_memcpy(g_sort_buffer->data, right - rhs[1],
			rhs[1] * sizeof(int)) + rhs[1] - 1;
	i = lhs[1];
	j = rhs[1];
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

void			ft_timsort_merge_if_three(unsigned int stack[][2],
		int stack_size, unsigned int const arr_sizes[3], int *data)
{
	if (arr_sizes[0] <= arr_sizes[2])
	{
		arr_sizes[0] <= arr_sizes[1] ?
		ft_merge_right(data, stack[stack_size - 1], stack[stack_size]) :
		ft_merge_left(data, stack[stack_size - 1], stack[stack_size]);
		stack[stack_size - 1][1] = arr_sizes[1] + arr_sizes[0];
	}
	else
	{
		arr_sizes[2] <= arr_sizes[1] ?
		ft_merge_left(data, stack[stack_size - 2], stack[stack_size - 1]) :
		ft_merge_right(data, stack[stack_size - 2], stack[stack_size - 1]);
		stack[stack_size - 2][1] = arr_sizes[2] + arr_sizes[1];
		((void**)stack)[stack_size - 1] = ((void**)stack)[stack_size];
	}
}

void			ft_merge_rest(unsigned int stack[][2],
		int stack_size, unsigned int arr_sizes[3], int *data)
{
	while (--stack_size > 0)
	{
		arr_sizes[0] = stack[stack_size][1];
		arr_sizes[1] = stack[stack_size - 1][1];
		arr_sizes[0] <= arr_sizes[1] ?
		ft_merge_right(data, stack[stack_size - 1], stack[stack_size]) :
		ft_merge_left(data, stack[stack_size - 1], stack[stack_size]);
		stack[stack_size - 1][1] = arr_sizes[1] + arr_sizes[0];
	}
}

int				ft_merge_if_need(unsigned int stack[][2],
		int stack_size, unsigned int *arr_sizes, int *data)
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
			stack[stack_size - 1][1] = arr_sizes[1] + arr_sizes[0];
		}
		else if (stack_size >= 3 && arr_sizes[2] <= arr_sizes[1] + arr_sizes[0]
			&& --stack_size)
			ft_timsort_merge_if_three(stack, stack_size, arr_sizes, data);
	}
	return (stack_size);
}
