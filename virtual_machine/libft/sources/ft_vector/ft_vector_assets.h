/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_assets.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:02:19 by dwiegand          #+#    #+#             */
/*   Updated: 2019/07/04 17:01:23 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_FT_VECTOR_ASSETS_H
# define LIBFT_FT_VECTOR_ASSETS_H

# include "ft_vector.h"
# include "ft_project_assets.h"
# include "ft_memory.h"

struct		s_vector_data
{
	void		**begin;
	size_t		end;
	size_t		size;
	void		(*free)(void **p);
};

# define V_DATA(x)		((struct s_vector_data*)(x)->data)

void		**ft_vector_begin(const t_vector *this);
void		**ft_vector_end(const t_vector *this);
void		ft_vector_push_back(t_vector *this, void *elem);
size_t		ft_vector_size(const t_vector *this);
void		ft_vector_delete_elem(t_vector *this, size_t index);

void		ft_vector_cat(t_vector *const this, const t_vector *const p);
void		ft_vector_destroy_tool(t_vector *p);

#endif
