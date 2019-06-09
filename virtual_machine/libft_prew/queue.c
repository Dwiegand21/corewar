/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 12:25:54 by dwiegand          #+#    #+#             */
/*   Updated: 2019/04/04 18:40:20 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "queue.h"

static int		print(t_queue *p)
{
	int		*cur;
	int		i;

	if (!(i = p->size(p)))
		return (0);
	if (((t_qeueprvt *)(p->prvt))->last
		== ((t_qeueprvt *)(p->prvt))->que)
		cur = ((t_qeueprvt *)(p->prvt))->que
			+ ((t_qeueprvt *)(p->prvt))->s;
	else
		cur = ((t_qeueprvt *)(p->prvt))->last - 1;
	while (i--)
	{
		ft_putnbr(*cur);
		if (cur == ((t_qeueprvt *)(p->prvt))->que)
			cur = ((t_qeueprvt *)(p->prvt))->que
			+ ((t_qeueprvt *)(p->prvt))->s;
		else
			cur -= 1;
		if (i)
			ft_putchar(' ');
	}
	ft_putchar('\n');
	return (1);
}

static int		pop(t_queue *p)
{
	if (((t_qeueprvt *)(p->prvt))->last
		== ((t_qeueprvt *)(p->prvt))->que)
	{
		((t_qeueprvt *)(p->prvt))->last =
			((t_qeueprvt *)(p->prvt))->que
			+ ((t_qeueprvt *)(p->prvt))->s;
	}
	else
	{
		((t_qeueprvt *)(p->prvt))->last -= 1;
	}
	if (((t_qeueprvt *)(p->prvt))->last == ((t_qeueprvt *)(p->prvt))->first)
		ft_error("error: queue is empty\n", 22);
	return (*((t_qeueprvt *)(p->prvt))->last);
}

static void		push(t_queue *p, int value)
{
	*(((t_qeueprvt *)(p->prvt))->first) = value;
	if (((t_qeueprvt *)(p->prvt))->first
		== ((t_qeueprvt *)(p->prvt))->que)
	{
		((t_qeueprvt *)(p->prvt))->first =
			((t_qeueprvt *)(p->prvt))->que
			+ ((t_qeueprvt *)(p->prvt))->s;
	}
	else
		((t_qeueprvt *)(p->prvt))->first -= 1;
	if (((t_qeueprvt *)(p->prvt))->first == ((t_qeueprvt *)(p->prvt))->last - 1)
		ft_error("error: queue is full\n", 21);
	return ;
}

static int		size(t_queue *p)
{
	if (((t_qeueprvt *)(p->prvt))->first <
		((t_qeueprvt *)(p->prvt))->last)
	{
		return (((t_qeueprvt *)(p->prvt))->last
			- ((t_qeueprvt *)(p->prvt))->first - 1);
	}
	else
		return ((((t_qeueprvt *)(p->prvt))->s -
			(((t_qeueprvt *)(p->prvt))->first
			- ((t_qeueprvt *)(p->prvt))->que))
			+ (((t_qeueprvt *)(p->prvt))->last
			- ((t_qeueprvt *)(p->prvt))->que));
}

t_queue			*queue_create(int n)
{
	t_queue		*p;

	p = NULL;
	if (!n)
		return (p);
	if (!(p = (t_queue *)malloc(sizeof(t_queue))))
		ft_error("error: memory allocation error\n", 31);
	if (!(p->prvt = (void *)malloc(sizeof(t_qeueprvt))))
		ft_error("error: memory allocation error\n", 31);
	p->pop = &pop;
	p->push = &push;
	p->size = &size;
	p->print = &print;
	((t_qeueprvt *)(p->prvt))->s = n;
	if (!(((t_qeueprvt *)(p->prvt))->que =
		(int *)malloc(sizeof(int) * (n + 1))))
		ft_error("error: memory allocation error\n", 31);
	((t_qeueprvt *)(p->prvt))->last = ((t_qeueprvt *)(p->prvt))->que
		+ ((t_qeueprvt *)(p->prvt))->s;
	((t_qeueprvt *)(p->prvt))->first = ((t_qeueprvt *)(p->prvt))->que
		+ ((t_qeueprvt *)(p->prvt))->s - 1;
	return (p);
}
