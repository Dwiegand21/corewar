/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 12:23:54 by dwiegand          #+#    #+#             */
/*   Updated: 2019/03/24 12:25:39 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

typedef struct	s_matrix
{
	int		**matrix;
	int		size_y;
	int		size_x;
}				t_matrix;

void			ft_error(char *error, int size);
void			ft_putchar(char c);
void			ft_putnbr(int nbr);
void			*ft_memalloc(unsigned long size);

t_matrix		*matrix_create(int y, int x);
int				matrix_delete(t_matrix **a);
int				matrix_print(t_matrix *a);
t_matrix		*matrix_multiply(t_matrix *a, t_matrix *b);

#endif
