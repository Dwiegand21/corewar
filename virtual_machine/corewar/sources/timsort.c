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
static inline void	ft_merge_left(int *data, unsigned int lhs[2], unsigned int rhs[2])
{
	const unsigned int	zl = lhs[1];
	const unsigned int	zr = rhs[1];
	int					buffer[zl];
	unsigned int 		i;
	unsigned int 		j;
	int 				*left;
	int 				*right;
	int 				*buf;

	left = data + lhs[0] - 1;
	right = data + rhs[0];
	buf = ft_memcpy(buffer, left + 1, zl * sizeof(int));
	i = 0;
	j = 0;
	while (i < zl && j < zr && ++left)
		if (*buf <= *right && ++i)
			*left = *buf++;
		else if (++j)
			*left = *right++;
	while (i++ < zl && ++left)
		*left = *buf++;
	while (j++ < zr && ++left)
		*left = *right++;
}

// todo rhs->size need to be less than lhs->size
static inline void	ft_merge_right(int *data, unsigned int lhs[2], unsigned int rhs[2])
{
	const unsigned int	zl = lhs[1];
	const unsigned int	zr = rhs[1];
	int					buffer[zl];
	unsigned int 		i;
	unsigned int 		j;
	int 				*left;
	int 				*right;
	int 				*buf;

	left = data + lhs[0] + zl - 1;
	right = data + rhs[0] + zr;
	buf = (int*)ft_memcpy(buffer, right - zr, zr * sizeof(int)) + zr - 1;
	i = zl;
	j = zr;
	while (i > 0 && j > 0 && --right)
		if (*buf > *left && j--)
			*right = *buf--;
		else if (i--)
			*right = *left--;
	while (j-- > 0 && --right)
		*right = *buf--;
	while (i-- > 0 && --right)
		*right = *left--;


//	printf("\n");
//	for (size_t e = 0; e < 100; ++e)
//	{
//		printf("%3d ", data[e]);
//	}
//	printf("\n");
}


// todo change fucking defines to variables
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
	stack_size = 0;
	ft_bzero(subarrays, (len / minrun + 1) * 2 * sizeof(int));
	ft_bzero(stack, (len / minrun + 1) * 2 * sizeof(int));
	while (end < len)
	{
		stack[stack_size][0] = end;
		stack[stack_size][1] = (data == array_end) ? 1u : ft_find_subarray_len(data + end + 1, minrun, array_end);
		end += stack[stack_size++][1];

		while (!((stack_size < 3 || BOT_ARR_SIZE > MID_ARR_SIZE + TOP_ARR_SIZE) && (stack_size < 2 || MID_ARR_SIZE > TOP_ARR_SIZE))) // todo try without !
		{
			if (stack_size >= 2 && MID_ARR_SIZE <= TOP_ARR_SIZE)
			{
				ft_merge_left(data, stack[stack_size - 2], stack[stack_size - 1]);
				stack[stack_size - 2][1] = MID_ARR_SIZE + TOP_ARR_SIZE;
				--stack_size;
			}
			if (stack_size >= 3 && BOT_ARR_SIZE <= MID_ARR_SIZE + TOP_ARR_SIZE)
			{
				if (TOP_ARR_SIZE <= BOT_ARR_SIZE)
				{
					TOP_ARR_SIZE <= MID_ARR_SIZE ?
					ft_merge_right(data, stack[stack_size - 2], stack[stack_size - 1]) :
					ft_merge_left(data, stack[stack_size - 2], stack[stack_size - 1]);
					stack[stack_size - 2][1] = MID_ARR_SIZE + TOP_ARR_SIZE;
					--stack_size;
				}
				else
				{
					BOT_ARR_SIZE <= MID_ARR_SIZE ?
					ft_merge_left(data, stack[stack_size - 3], stack[stack_size - 2]) :
					ft_merge_right(data, stack[stack_size - 3], stack[stack_size - 2]);
					stack[stack_size - 3][1] = BOT_ARR_SIZE + MID_ARR_SIZE;
					stack[stack_size - 2][0] = stack[stack_size - 1][0];
					stack[stack_size - 2][1] = stack[stack_size - 1][1];
					//((void**)stack)[stack_size - 2] = ((void**)stack)[stack_size - 1];
					--stack_size;
				}
			}
		}

//		subarrays[subarrays_count][0] = end;
//		subarrays[subarrays_count][1] = (data == array_end) ? 1u : ft_find_subarray_len(data + end + 1, minrun, array_end);
//		end += subarrays[subarrays_count++][1];
	}

	curr_subarr = 0;

//	while (curr_subarr < subarrays_count)
//	{
//		push_to_stack(curr_subarr, subarrays, stack, stack_size++);
//		while (!((stack_size < 3 || BOT_ARR_SIZE > MID_ARR_SIZE + TOP_ARR_SIZE) && (stack_size < 2 || MID_ARR_SIZE > TOP_ARR_SIZE))) // todo try without !
//		{
//			if (stack_size >= 2 && MID_ARR_SIZE <= TOP_ARR_SIZE)
//			{
//				 ft_merge_left(data, stack[stack_size - 2], stack[stack_size - 1]);
//				 stack[stack_size - 2][1] = MID_ARR_SIZE + TOP_ARR_SIZE;
//				 --stack_size;
//			}
//			if (stack_size >= 3 && BOT_ARR_SIZE <= MID_ARR_SIZE + TOP_ARR_SIZE)
//			{
//				if (TOP_ARR_SIZE <= BOT_ARR_SIZE)
//				{
//					TOP_ARR_SIZE <= MID_ARR_SIZE ?
//					ft_merge_right(data, stack[stack_size - 2], stack[stack_size - 1]) :
//					ft_merge_left(data, stack[stack_size - 2], stack[stack_size - 1]);
//					stack[stack_size - 2][1] = MID_ARR_SIZE + TOP_ARR_SIZE;
//					--stack_size;
//				}
//				else
//				{
//					BOT_ARR_SIZE <= MID_ARR_SIZE ?
//					ft_merge_left(data, stack[stack_size - 3], stack[stack_size - 2]) :
//					ft_merge_right(data, stack[stack_size - 3], stack[stack_size - 2]);
//					stack[stack_size - 3][1] = BOT_ARR_SIZE + MID_ARR_SIZE;
//					stack[stack_size - 2][0] = stack[stack_size - 1][0];
//					stack[stack_size - 2][1] = stack[stack_size - 1][1];
//					//((void**)stack)[stack_size - 2] = ((void**)stack)[stack_size - 1];
//					--stack_size;
//				}
//			}
//		}
//		++curr_subarr;
//	}
	while (stack_size > 1)
	{
		TOP_ARR_SIZE <= MID_ARR_SIZE ?
		ft_merge_right(data, stack[stack_size - 2], stack[stack_size - 1]) :
		ft_merge_left(data, stack[stack_size - 2], stack[stack_size - 1]);
		stack[stack_size - 2][1] = MID_ARR_SIZE + TOP_ARR_SIZE;
		--stack_size;
	}


	if (ft_check_sorted(data, len))
	{
		//printf("OK\n");
	}
	else
	{
		printf("KO: ");
		for (size_t e = 0; e < len; ++e)
		{
			printf("%3d ", data[e]);
			if ((e + 1) % minrun == 0)
				printf("| ");
		}
		printf("\n");
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

	//printf("MINRUN IS: %d\n", minrun);


	ft_timsort_split_and_merge(data, len, minrun, array_end);
//	while (data < array_end)
//	{
//		unsigned int act_minrun = (array_end - data >= minrun) ? minrun : array_end - data;
//
//		if (!ft_check_sorted(data, (int)act_minrun))
//		{
//			printf("HUI(%d)\n", minrun);
//		}
//		data += act_minrun;
//	}
	// todo if len <= 64   {ft_insert_sort}
}

void ft_timsort_test(void)
{
	ft_test_sort(10000, 1000);

}