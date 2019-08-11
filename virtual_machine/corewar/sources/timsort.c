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


//	printf("BEFORE: ");
//	for (size_t e = 0; e < len; ++e)
//	{
//		printf("%3d ", data[e]);
//	}
//	printf("\nAFTER: ");


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

//	for (size_t e = 0; e < len; ++e)
//	{
//		printf("%3d ", data[e]);
//	}
//	printf("\n");
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
	//printf("LEN BEF: %d minrun:%d\n", len, minrun);
	//printf("1: %ld 2:%d\n", array_end - start, minrun);
	if (len < minrun)
	{
		len = array_end - start >= minrun ? minrun : array_end - start;
		ft_insertion_sort(start, len);
	}
	//printf("LEN AFT: %d\n", len);

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
//	len = max_size;

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


//	int *array_src = malloc(sizeof(int) * len);
//	ft_memcpy(array_src, data, sizeof(int) * len);


//	printf("{");
//	for (size_t e = 0; e < len; ++e)
//	{
//		printf("%d, ", data[e]);
//		if ((e + 1) % minrun == 0)
//			printf(" | ");
//	}
//	printf("}\n");

	ft_bzero(subarrays, 64 * 2 * sizeof(int)); // todo count it before?

	while (end < len)
	{
		unsigned int ln = (data == array_end) ? 1u : ft_find_subarray_len(data + end + 1, minrun, array_end);
		//printf("end: %d  len: %d\n", end, ln);
		end += ln;
	}

	int *start = data;
	int limit = 0;
	while (data < array_end)
	{
		unsigned int act_minrun = (array_end - data >= minrun) ? minrun : array_end - data;
//		printf("%d %c\n", act_minrun, ft_check_sorted(data, (int)act_minrun) ? '+' : '-');
//
//		for (int e = 0; e < act_minrun; ++e)
//		{
//			printf("%d ", data[e]);
//		}
//		printf("\n");
//		if (++limit == 10)
//			break ;

		if (!ft_check_sorted(data, (int)act_minrun))
		{
			printf("HUI(%d)\n", minrun);
//			printf("{");
//			for (size_t e = 0; e < len; ++e)
//			{
//				printf("%3d, ", array_src[e]);
//				if ((e + 1) % 10 == 0)
//					printf("\n");
//			}
//			printf("}");
//			break ;
		}
		else
		{
			//printf("GG\n");
		}
		data += act_minrun;
	}




//	printf("(%d) ", minrun);
//	for (size_t e = 0; e < len; ++e)
//	{
//		printf("%3d ", data[e]);
//		if ((e + 1) % minrun == 0)
//			printf(" | ");
//	}
//	printf("\n\n");

	// todo if len <= 64   {ft_insert_sort}

}

void ft_timsort_test(void)
{
	ft_test_sort(1000000, 10000);

//	int tst[] = {979, 260, 699, 769, 185, 368, 366, 262, 605, 72,
//			     657, 851, 981, 783, 100, 43, 235, 536, 978, 370,
//			     721, 923, 136, 50, 655, 498, 176,152, 475, 571,
//			     326, 166, 828, 14, 998, 857, 935, 560, 795, 361,
//			     758, 875, 218, 219, 743, 906, 603, 122, 357, 30,
//
//			     177, 805, 986, 393, 999, 757, 21, 252, 395, 870,
//			     399, 296, 133, 420, 465, 436, 366, 365, 19, 666,
//			     727, 895, 914, 945, 724, 668, 579, 854, 537, 374,
//			     140, 740, 872, 989, 425, 891, 528, 181, 823, 117,
//			     960, 202, 733, 736, 723, 581, 637, 304, 477, 292};

//	int tst[] = {573, 998, 620, 446, 705, 766, 344,  98, 994, 262,
//				 956, 597, 682, 705, 196, 255, 100, 691, 983, 452,
//				 738, 649, 890, 669, 848, 537,  12, 121, 671, 475,
//				 214,  59,  83, 350, 508, 563, 544, 308, 976, 424,
//				  24, 269, 648, 185, 140, 149, 556, 811, 158, 304,
//				 170, 535,  67, 523, 629, 205, 226, 428,  84, 609,
//				 939, 134, 295, 630, 188, 222, 209,  83, 550, 746,
//				  43, 764, 174, 115, 844, 699, 106, 182, 803, 605,
//				 741,  13, 480, 316, 283, 778, 251, 897,  24,  95,
//				 640, 942, 520, 391, 170, 697, 217, 449, 878, 569,
//				 949, 521, 856, 630, 218, 547, 478, 731, 898, 554,
//				 332, 106, 451, 659, 148, 398, 697, 820,  30, 699,
//				  81, 283, 606, 118, 396, 293, 982, 840,  86, 960,
//				 438, 175, 309, 836, 436, 795, 817, 398, 245, 904,
//				  14,  92, 792, 603, 488,  28, 121, 262, 870,  78,
//				 770, 401, 933, 132, 404, 568, 743, 610,  77, 319,
//				 732, 252, 226, 583, 457, 873,  67, 605, 502, 632,
//				 386, 420, 784, 617, 917, 317, 784, 127, 612, 136,
//				  85, 853, 986, 356,  97, 378, 165, 760,   0, 327,
//				 734, 106, 607, 764, 321, 934, 326, 730, 840, 996,
//				 844, 138, 532, 160, 746, 345, 203, 456, 911, 701,
//				 588, 305, 643, 901, 795, 521, 813, 154, 996, 740,
//				 424, 614, 406,  47, 180, 364, 375, 361, 128, 604,
//				  75, 477, 115, 952, 843,  24, 594, 109, 833,  26,
//				 396, 519, 114, 699, 290, 114, 295, 648, 623, 842,
//				 965, 820, 243, 521, 724, 788, 692, 702, 609, 680,
//				 100, 321, 506, 121, 102, 990, 365, 195, 865, 544,
//				 125, 212, 371, 126, 816, 941, 227, 308, 851, 198,
//				 308, 882,  66, 705, 945, 319, 728, 486, 728, 199,
//				 939,  49, 832, 329, 565, 307, 675, 253, 666, 595};
//
//	ft_timsort_int(tst, 300);





//	for (size_t i = 1; i < 4000000000; i *= 5)
//	{
//		printf("%zu - %d\n", i, ft_get_minrun(i));
//	}
}