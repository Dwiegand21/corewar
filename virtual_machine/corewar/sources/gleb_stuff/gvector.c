/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_vector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 18:39:46 by ggerardy          #+#    #+#             */
/*   Updated: 2019/07/08 18:39:46 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "gvector.h"

void				*gft_realloc(void *old_data, size_t prev_size,
								size_t new_size)
{
	void	*new_data;
	size_t	i;

	if (!old_data)
		return (0);
	new_data = ft_memalloc(new_size);
	if (!new_data)
	{
		free(old_data);
		return (0);
	}
	i = 0;
	while (i < prev_size && i < new_size)
	{
		((char*)new_data)[i] = ((char*)old_data)[i];
		++i;
	}
	free(old_data);
	return (new_data);
}

static inline void	gft_free_array(void **arr, size_t size,
									void (*free_data)(void*))
{
	size_t i;

	if (!free_data)
		return ;
	i = (size_t)-1;
	while (++i < size)
	{
		free_data(arr[i]);
	}
}

void				*gft_realloc_free(void *old_data, size_t prev_size,
									 size_t new_size, void (*free_data)(void*))
{
	void	*new_data;
	size_t	i;

	if (!old_data)
		return (0);
	new_data = ft_memalloc(new_size);
	if (!new_data)
	{
		free(old_data);
		gft_free_array(old_data, prev_size, free_data);
		return (0);
	}
	i = 0;
	while (i < prev_size && i < new_size)
	{
		((char*)new_data)[i] = ((char*)old_data)[i];
		++i;
	}
	free(old_data);
	return (new_data);
}

t_gvector		*gft_vector_cpy(const t_gvector *src)
{
	t_gvector *v;

	if (!src)
		return (0);
	if (!(v = gft_make_vector(src->capacity)) || !ft_memcpy(v->data, src->data,
														   sizeof(void*) * src->capacity))
		return (0);
	v->capacity = src->capacity;
	v->len = src->len;
	v->offset = src->offset;
	return (v);
}

t_gvector		*gft_make_vector(size_t init_size)
{
	t_gvector *v;

	v = (t_gvector*)ft_memalloc(sizeof(t_gvector) * 1);
	if (!v)
		return (0);
	v->capacity = init_size <= 1 ? 2 : init_size;
	v->data = (void**)malloc(sizeof(void*) * (v->capacity));
	if (!v->data)
	{
		free(v);
		return (0);
	}
	v->data[0] = 0;
	return (v);
}

t_gvector		*gft_make_vector_free(size_t init_size, void (*free_data)(void*))
{
	t_gvector *v;

	if (!(v = gft_make_vector(init_size)))
		return (0);
	v->free_data = free_data;
	return (v);
}

int				gft_vector_push_back(t_gvector **v_ptr, void *c)
{
	t_gvector *v;

	if (!v_ptr || !*v_ptr)
		return (-1);
	v = *v_ptr;
	if (v->len == v->capacity - 1)
	{
		v->data = gft_realloc_free(v->data, v->capacity * sizeof(void*),
								  v->capacity * 2 * sizeof(void*), (*v_ptr)->free_data);
		if (!v->data)
		{
			gft_free_vector(v_ptr);
			return (0);
		}
		v->capacity *= 2;
	}
	v->data[v->len++] = c;
	v->data[v->len] = 0;
	return (1);
}

void				gft_free_vector_simple(void *v_ptr)
{
	t_gvector *v;

	v = v_ptr;
	if (!v)
		return ;
	gft_free_array(v->data, v->len, v->free_data);
	free(v->data);
	free(v);
}

void				gft_free_vector(t_gvector **v)
{
	if (!v)
		return ;
	gft_free_vector_simple(*v);
	*v = 0;
}

int					gft_free_ret_vector(t_gvector **v, int ret)
{
	gft_free_vector(v);
	return (ret);
}

int					gft_vector_fit(t_gvector **v_ptr)
{
	t_gvector *v;

	if (!v_ptr || !*v_ptr)
		return (-1);
	v = *v_ptr;
	if (v->len == v->capacity - 1)
		return (1);
	v->data = gft_realloc_free(v->data, v->capacity * sizeof(void*),
							  (v->len == 0 ? 2 : v->len + 1) * sizeof(void*), v->free_data);
	if (!v->data)
	{
		gft_free_vector(v_ptr);
		return (0);
	}
	v->data[v->len] = 0;
	v->capacity = v->len == 0 ? 2 : v->len + 1;
	return (1);
}
