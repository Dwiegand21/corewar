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

static inline void	ft_insertion_sort(int *data, unsigned int len)
{
	int i;
	int j;
	int curr;

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

void	ft_timsort_int(int *data, size_t len)
{
	const unsigned int	minrun = ft_get_minrun(len);
	int *const			array_end = data + len;
	unsigned int		subarrays[64][2];
	unsigned int		end;

	end = 0;
	ft_bzero(subarrays, 64 * 2 * sizeof(int)); // todo count it before?
	while (end < len)
	{
		end += (data == array_end) ? 1u : ft_find_subarray_len(data + end + 1, minrun, array_end);
	}
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
	ft_test_sort(1000000, 10000);
}