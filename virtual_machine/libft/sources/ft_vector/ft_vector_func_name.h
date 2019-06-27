/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_func_name.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:02:19 by dwiegand          #+#    #+#             */
/*   Updated: 2019/06/27 21:33:43 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_FT_VECTOR_FUNC_NAME_H
# define LIBFT_FT_VECTOR_FUNC_NAME_H

# include "ft_vector.h"

struct		s_vector_data
{
	void		**begin;
	void 		**end;
	size_t 		size;
};

# define V_DATA(x)		((struct s_vector_data*)(x)->data)

void		*ft_vector_begin(const t_vector *this);
void		*ft_vector_end(const t_vector *this);
void		ft_vector_push_back(t_vector *this, void *elem);
void 		ft_vector_join(t_vector *this, t_vector *p);

#endif
