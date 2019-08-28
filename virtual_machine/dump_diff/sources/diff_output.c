/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diff_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 08:00:31 by axtazy            #+#    #+#             */
/*   Updated: 2019/06/07 13:58:23 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dump_diff.h"

static int		line_length(const char *str)
{
	int 	length = 0;

	while(str[length] != 0 && str[length] != '\n')
	{
		length++;
	}
	return (length);
}

static int 		biggest_length(char *s1, char *s2)
{
	int 	length1 = line_length(s1);
	int 	length2 = line_length(s2);

	if (length1 > length2)
		return (length1);
	else
		return (length2);
}

static int		end_of_line(char c)
{
	if (c == 0 || c == '\n')
		return (1);
	return (0);
}

static void		putchar_c(char c, int color)
{
	if (color == 1)
	{
		write(1, RED, 7);
		write(1, &c, 1);
		write(1, RESET, 4);
	}
	else if (color == 2)
	{
		write(1, GREEN, 7);
		write(1, &c, 1);
		write(1, RESET, 4);
	}
	else if (color == 3)
	{
		write(1, W_BRED, 8);
		write(1, &c, 1);
		write(1, RESET, 4);
	}
	else
	{
		write(1, W_BGREEN, 8);
		write(1, &c, 1);
		write(1, RESET, 4);
	}
}

static int		compare_lines(char* this, char* cmp, int length, int color)
{
	int 	n_diff = 0;
	int 	i = 0;

	if (color == 2)
	{
		cmp += 9;
		this += 9;
		i += 9;
		write(1, "         ", 9);
	}
	while (!end_of_line(*this))
	{
		if (*cmp == *this)
		{
			write(1, this, 1);
			cmp++;
		}
		else
		{
			putchar_c(*this, color);
			if (*cmp != 0)
				cmp++;
			n_diff++;
		}
		this++;
		i++;
	}
	while (i < length)
	{
		putchar_c(' ', color + 2);
		n_diff++;
		i++;
	}
	write(1, "\n", 1);
	return (n_diff);
}

int				compare_output(t_dump *dd)
{
	char* 	origin = dd->strings->origin;
	char* 	our = dd->strings->our;
	int 	diff_status = 0;
	int 	length;

	while (*origin != 0 || *our != 0)
	{
		length = biggest_length(origin, our);
		diff_status += compare_lines(origin, our, length, 1);
		compare_lines(our, origin, length, 2);
		our += line_length(our);
		origin += line_length(origin);
		if (*our == '\n')
			our++;
		if (*origin == '\n')
			origin++;
	}
	return (0);
}