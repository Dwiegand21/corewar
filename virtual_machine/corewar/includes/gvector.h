/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_gvector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 18:43:00 by ggerardy          #+#    #+#             */
/*   Updated: 2019/07/08 18:43:00 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GVECTOR_H
#define GVECTOR_H

#include <stdlib.h>

typedef struct	s_gvector
{
	void		**data;
	size_t		len;
	size_t		capacity;
	int			offset;
	void		(*free_data)(void*);
}				t_gvector;

t_gvector		*gft_make_vector(size_t init_size);
t_gvector		*gft_make_vector_free(size_t init_size,
									 void (*free_data)(void*));
t_gvector		*gft_vector_cpy(const t_gvector *src);
void			gft_free_vector(t_gvector **v);
void			gft_free_vector_simple(void *v);
int				gft_free_ret_vector(t_gvector **v, int ret);
int				gft_vector_push_back(t_gvector **v_ptr, void *c);
int				gft_vector_fit(t_gvector **v_ptr);

#endif //GVECTOR_H
