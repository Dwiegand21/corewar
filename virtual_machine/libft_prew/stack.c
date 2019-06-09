/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 12:28:36 by dwiegand          #+#    #+#             */
/*   Updated: 2019/03/24 12:33:22 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "stack.h"

static int		pop(t_stack *p)
{
	if (!((t_stckprvt *)(p->prvt))->top)
		ft_error("error: stack is empty\n", 22);
	((t_stckprvt *)(p->prvt))->last -= 1;
	((t_stckprvt *)(p->prvt))->top -= 1;
	return (*(((t_stckprvt *)(p->prvt))->last));
}

static void		push(t_stack *p, int value)
{
	if (((t_stckprvt *)(p->prvt))->top == ((t_stckprvt *)(p->prvt))->s)
		ft_error("error: stack is full\n", 21);
	*(((t_stckprvt *)(p->prvt))->last) = value;
	((t_stckprvt *)(p->prvt))->top += 1;
	((t_stckprvt *)(p->prvt))->last += 1;
	return ;
}

static int		size(t_stack *p)
{
	return (((t_stckprvt *)(p->prvt))->top);
}

static int		print(t_stack *p)
{
	int			i;

	i = 0;
	if (i == ((t_stckprvt *)(p->prvt))->top)
	{
		return (0);
	}
	while (i < ((t_stckprvt *)(p->prvt))->top)
	{
		ft_putnbr(*(((t_stckprvt *)(p->prvt))->stack + i));
		i++;
		if (i < ((t_stckprvt *)(p->prvt))->top)
			ft_putchar(' ');
	}
	ft_putchar('\n');
	return (1);
}

t_stack			*stack_create(int n)
{
	t_stack		*p;

	p = NULL;
	if (!(p = (t_stack *)malloc(sizeof(t_stack))))
		ft_error("error: memory allocation error\n", 31);
	if (!(p->prvt = (t_stckprvt *)malloc(sizeof(t_stckprvt))))
		ft_error("error: memory allocation error\n", 31);
	p->pop = &pop;
	p->push = &push;
	p->size = &size;
	p->print = &print;
	((t_stckprvt *)(p->prvt))->s = n;
	if (!(((t_stckprvt *)(p->prvt))->stack =
		(int *)malloc(sizeof(int) * (n + 1))))
		ft_error("error: memory allocation error\n", 31);
	((t_stckprvt *)(p->prvt))->last = ((t_stckprvt *)(p->prvt))->stack;
	((t_stckprvt *)(p->prvt))->top = 0;
	return (p);
}
