/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diff_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 08:00:31 by axtazy            #+#    #+#             */
/*   Updated: 2019/06/12 14:45:45 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compare_dumps.h"

int 		position = 0;

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
	if (color == 0)
	{
		write(1, &c, 1);
	}
	else if (color == 1)
	{
		write(1, RED, 7);
		write(1, &c, 1);
	}
	else if (color == 2)
	{
		write(1, GREEN, 7);
		write(1, &c, 1);
	}
	else if (color == 3)
	{
		write(1, W_BRED, 8);
		write(1, &c, 1);
	}
	else
	{
		write(1, W_BGREEN, 8);
		write(1, &c, 1);
	}
	write(1, RESET, 4);
}

static t_list*	lstdel(t_list *list, int pc)
{
	t_list*	cur;

	while (list && ((t_process *)((list)->content))->pc == pc)
	{
		cur = list->next;
		free(list);
		list = cur;
	}
	return (list);
}

static t_list*	process_pos(t_list *list, char *str)
{


	if (list == NULL)
		return NULL;
	if (((t_process *)((list)->content))->pc == position)
	{
		write(1, W_BYELLOW, 8);
		if (*(str + 1) == ' ')
		{
			return (lstdel(list, ((t_process *)((list)->content))->pc));
		}
	}
	return (list);
}

static int		compare_lines(	t_list** list,
								char* this,
								char* cmp,
								int length,
								int color )
{
	int 	n_diff = 0;
	int 	i = 0;

	if (color == 1)
	{
		write(1, "         ", 9);
	}
	else
	{
		write(1, this, 9);
	}
	cmp += 9;
	this += 9;
	i += 9;
	while (!end_of_line(*this))
	{
		if (color == 2)
		{
			*list = process_pos(*list, this);
		}
		if (*cmp == *this)
		{
			putchar_c(*this, 0);
			cmp++;
		}
		else
		{
			putchar_c(*this, color);
			if (*cmp != 0)
				cmp++;
			n_diff++;
		}
		if (color == 2 && *this == ' ')
			position++;
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

	//ft_lstiter(dd->processes, &data_print);
	while (*origin != 0 || *our != 0)
	{
		length = biggest_length(origin, our);
		diff_status += compare_lines(&dd->processes, our, origin, length, 2);
		if (ORIGIN)
			compare_lines(&dd->processes, origin, our, length, 1);
		our += line_length(our);
		origin += line_length(origin);
		if (*our == '\n')
			our++;
		if (*origin == '\n')
			origin++;
	}
	//printf("last pos: %d\n", position);
	return (0);
}