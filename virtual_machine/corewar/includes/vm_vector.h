/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vm_vector.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 18:10:06 by ggerardy          #+#    #+#             */
/*   Updated: 2019/08/14 18:10:06 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_VECTOR_H
#define VM_VECTOR_H

#include <stdlib.h>
#include <libft.h>

typedef struct	s_vm_vector_int
{
	int			*data;
	int			len;
	int			capacity;
	int			offset;
}				t_vm_vector_int;

t_vm_vector_int* 	ft_make_vm_vector_int(size_t init_size);
t_vm_vector_int* 	ft_vm_vector_int_cpy(const t_vm_vector_int *src);
void				ft_free_vm_vector_int(t_vm_vector_int **v);
void				ft_free_vm_vector_int_simple(void *v);
int					ft_free_ret_vm_vector_int(t_vm_vector_int **v, int ret);
char				ft_vm_vector_int_push_back(t_vm_vector_int **v_ptr, int c);
char				ft_vm_vector_int_fit(t_vm_vector_int **v_ptr);

#endif
