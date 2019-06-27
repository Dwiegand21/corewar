/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 18:22:27 by dwiegand          #+#    #+#             */
/*   Updated: 2019/06/27 21:26:01 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIRTUAL_MACHINE_FT_VECTOR_H
# define VIRTUAL_MACHINE_FT_VECTOR_H

# include <stdlib.h>

typedef struct s_vector		t_vector;

struct		s_vector
{
	void		**v;
	void		*(*begin)(const t_vector * this);
	void		*(*end)(const t_vector * this);
	void		(*push_back)(t_vector *this, void *);
	void		(*join)(t_vector *this, t_vector *p);
	void 		*data;
};

t_vector		*ft_vector_init(size_t size, size_t elem_size);
void			ft_vector_delete(t_vector **p);

#endif
