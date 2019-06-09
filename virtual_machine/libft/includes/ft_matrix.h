/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 05:11:29 by axtazy            #+#    #+#             */
/*   Updated: 2019/06/09 05:11:29 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_2_0_FT_MATRIX_H
# define LIBFT_2_0_FT_MATRIX_H

#include <stdlib.h>

typedef struct	s_matrix
{
	int		**matrix;
	int		size_y;
	int		size_x;
}				t_matrix;

t_matrix		*matrix_create(int y, int x);
int				matrix_delete(t_matrix **a);
int				matrix_print(t_matrix *a);
t_matrix		*matrix_multiply(t_matrix *a, t_matrix *b);


#endif
