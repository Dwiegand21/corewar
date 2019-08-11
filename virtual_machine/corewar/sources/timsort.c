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

#include "libft.h"
#include <stdio.h>

void	ft_timsort_int(int *data, size_t len);


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
		while (j > 0 && data[j - 1] > curr)
		{
			data[j] = data[j - 1];
			--j;
		}
		data[j] = curr;
	}
}

/// note only array bigger than 2
/// note send (data + 1)
static inline unsigned int	ft_find_subarray_len(int *data, unsigned int minrun,
		const int *array_end)
{
	unsigned int		len;
	const unsigned int	reverse = (data[-1] <= *data ? 0 : 1);
	int *const			start = data - 1;

	len = 1;
	while (data < array_end && ((data[-1] <= *data) ^ reverse))
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


int ft_check_sorted(const int *data, int len)
{
	for (int i = 0; i < len - 1; ++i)
	{
		if (data[i] > data[i + 1])
			return (0);
	}
	return (1);
}

#include <stdlib.h>
#include <time.h>

int ft_fill_rand_array(int *arr, int max_size)
{
	srand(time(NULL) + rand());
	int len = rand() % max_size + 64;
	len = max_size;

	for (int i = 0; i < len; ++i)
	{
		arr[i] = rand() % 1000;
	}
	return (len);
}

void ft_test_sort(int maxsize, int try_count)
{
	int *arr = malloc(sizeof(int) * maxsize);
	int i = -1;

	while (++i < try_count)
	{
		int len = ft_fill_rand_array(arr, maxsize);
		int before = ft_check_sorted(arr, len);
		ft_timsort_int(arr, len);
		//ft_insertion_sort(arr, len);
		int after = ft_check_sorted(arr, len);
		if (after != 1)
		{
			//printf("PIDOR SUKA!\n");
		}
		//else
		//	printf("GG\n");
	}
}

#define TOP_ARR_SIZE stack[stack_size - 1][1]
#define MID_ARR_SIZE stack[stack_size - 2][1]
#define BOT_ARR_SIZE stack[stack_size - 3][1]

static inline void push_to_stack(int curr_subarr, unsigned int subarrays[][2],
								 unsigned int stack[][2], int idx_stack)
{
	stack[idx_stack][0] = subarrays[curr_subarr][0];
	stack[idx_stack][1] = subarrays[curr_subarr][1];
}

static inline unsigned int ft_min(unsigned int a, unsigned int b)
{
	return (a <= b ? a : b);
}

// todo lhs->size need to be less than rhs->size
static inline void	ft_merge(int *data, unsigned int lhs[2], unsigned int rhs[2])
{
	const unsigned int	zl = lhs[1];
	const unsigned int	zr = rhs[1];
	int					buffer[zl];
	unsigned int 		i;
	unsigned int 		j;
	int 				*left;
	int 				*right;
	int					k;

	left = data + lhs[0];
	right = data + rhs[0];
	ft_memcpy(buffer, left, zl * sizeof(int));
	i = 0;
	j = 0;
	k = 0;
	while (i < zl && j < zr)
	{
		if (*left <= *right)
		{
			//buffer[]
		}
		else
		{

		}
	}
}

void	ft_timsort_split_and_merge(int *data, size_t len, unsigned int minrun, int *const array_end)
{
	unsigned int	subarrays[len / minrun + 1][2];
	unsigned int	end;
	int 			subarrays_count;
	unsigned int	stack[len / minrun + 1][2];
	int 			curr_subarr;
	int 			stack_size;

	end = 0;
	subarrays_count = 0;
	ft_bzero(subarrays, (len / minrun + 1) * 2 * sizeof(int));
	ft_bzero(stack, (len / minrun + 1) * 2 * sizeof(int));
	while (end < len)
	{
		subarrays[subarrays_count][0] = end;
		subarrays[subarrays_count][1] = (data == array_end) ? 1u : ft_find_subarray_len(data + end + 1, minrun, array_end);
		end += subarrays[subarrays_count++][1];
	}
	curr_subarr = 0;
	stack_size = 0;
	while (subarrays_count)
	{
		push_to_stack(curr_subarr, subarrays, stack, stack_size++);
		while (!((stack_size < 3 || BOT_ARR_SIZE > MID_ARR_SIZE + TOP_ARR_SIZE) && (stack_size < 2 || MID_ARR_SIZE > TOP_ARR_SIZE))) // todo try without !
		{
			if (stack_size >= 2 && MID_ARR_SIZE <= TOP_ARR_SIZE)
			{

			}
			if (stack_size >= 3 && BOT_ARR_SIZE <= MID_ARR_SIZE + TOP_ARR_SIZE)
			{

			}
		}
	}
	// todo if subarrays_count >= 3

}




void	ft_timsort_int(int *data, size_t len)
{
	const unsigned int	minrun = ft_get_minrun(len);
	int *const			array_end = data + len;
	unsigned int		subarrays[64][2];
	unsigned int		end;
	int 				subarays_count;

	ft_timsort_split_and_merge(data, len, minrun, array_end);
	while (data < array_end)
	{
		unsigned int act_minrun = (array_end - data >= minrun) ? minrun : array_end - data;

		if (!ft_check_sorted(data, (int)act_minrun))
		{
			printf("HUI(%d)\n", minrun);
		}
		data += act_minrun;
	}
	// todo if len <= 64   {ft_insert_sort}
}

void ft_timsort_test(void)
{
	//ft_test_sort(100000, 1000);

}