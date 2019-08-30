/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 12:23:39 by dwiegand          #+#    #+#             */
/*   Updated: 2019/06/09 10:01:31 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_matrix.h"
#include "ft_memory.h"
#include "ft_project_assets.h"
#include "ft_iostream.h"

t_matrix	*matrix_create(int y, int x)
{
	int			i;
	t_matrix	*p;

	i = 0;
	p = NULL;
	if (y <= 0 || x <= 0)
		return (p);
	if (!(p = (t_matrix *)malloc(sizeof(t_matrix))))
		ERRF(ERRALLOC);
	if (!(p->matrix = (int **)malloc(sizeof(int *) * y)))
		ERRF(ERRALLOC);
	p->size_x = x;
	p->size_y = y;
	while (i < y)
	{
		if (!(p->matrix[i] = ft_memalloc(sizeof(int) * x)))
			ERRF(ERRALLOC);
		i++;
	}
	return (p);
}

int			matrix_delete(t_matrix **p)
{
	int		i;

	i = 0;
	if (p && *p)
	{
		while (i < (*p)->size_y)
		{
			free((*p)->matrix[i]);
			i++;
		}
		free((*p)->matrix);
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}

t_matrix	*matrix_multiply(t_matrix *a, t_matrix *b)
{
	int			i;
	int			j;
	int			k;
	t_matrix	*new;

	if (!(a) || !(b) || a->size_x != b->size_y)
		return (NULL);
	new = matrix_create(a->size_y, b->size_x);
	i = 0;
	while (i < new->size_y)
	{
		j = 0;
		while (j < new->size_x)
		{
			k = 0;
			while (k < a->size_x)
			{
				new->matrix[i][j] += a->matrix[i][k] * b->matrix[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (new);
}

int			matrix_print(t_matrix *p)
{
	int		i;
	int		j;

	if (p == NULL)
		return (0);
	i = 0;
	while (i < p->size_y)
	{
		j = 0;
		while (j < p->size_x)
		{
			ft_putnbr(p->matrix[i][j]);
			j++;
			if (j < p->size_x)
				ft_putchar(' ');
		}
		ft_putchar('\n');
		i++;
	}
	return (1);
}
