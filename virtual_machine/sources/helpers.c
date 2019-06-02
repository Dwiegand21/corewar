/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 15:15:04 by axtazy            #+#    #+#             */
/*   Updated: 2019/05/29 15:15:04 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"


void	ft_print_endian()
{
	uint16_t	x;

	x = 1;
	if (*((uint8_t *) &x) == 0)
		write(1, "big-endian\n", 11);
	else
		write(1, "little-endian\n", 14);
}


void	ft_error(char*	error)
{
	int 	length;

//	if (PROJECT_NAME[0] != 0)
//	{
//		length = 0;
//		while (PROJECT_NAME[length])
//			length++;
//		write(2, PROJECT_NAME, length);
//		write(2, ": ", 2);
//	}
	length = 0;
	while (error[length])
		length++;
	write(2, error, length);
	exit(1);
}

void		bytes_reverse(void *param, size_t size)
{
	size_t 	i;
	char 	tmp;

	i = 0;
	while (i < size / 2)
	{
		tmp = *(((char *)param) + i);
		*(((char *)param) + i) = *(((char *)param) + size - 1 - i);
		*(((char *)param) + size - 1 - i) = tmp;
		i++;
	}
}

void		print_map(uint8_t *map)
{
	unsigned char	l;
	unsigned char	r;

	for (int i = 0; i < 64; i++)
	{
		for (int j = 0; j < 64; j++)
		{
			l = (((map[j + i * 64]) >> 4) & 0x0F);
			r = ((map[j + i * 64]) & 0x0F);
			if (l > 9)
				printf("%c", l % 10 + 'a');
			else
				printf("%c", l + '0');
			if (r > 9)
				printf("%c", r % 10 + 'a');
			else
				printf("%c", r + '0');
			printf(" ");
		}
		printf("\n");
	}
}
