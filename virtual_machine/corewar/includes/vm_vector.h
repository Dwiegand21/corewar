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
#include "vm_types.h"

t_vm_vector_int* 	ft_make_vm_vector_int(int init_size);
t_vm_vector_int		*ft_init_vm_vector_int(t_vm_vector_int *v, int init_size);
t_vm_vector_int* 	ft_vm_vector_int_cpy(const t_vm_vector_int *src);
void				ft_free_vm_vector_int(t_vm_vector_int **v);
void				ft_free_vm_vector_int_simple(void *v);
int					ft_free_ret_vm_vector_int(t_vm_vector_int **v, int ret);
char				ft_vm_vector_int_push_back(t_vm_vector_int *v_ptr, int c);
char 				ft_vm_vector_int_realloc(t_vm_vector_int *v); // todo myabe double pointer and auto-free??

t_vm_vector_prc* 	ft_make_vm_vector_prc(int init_size);
t_vm_vector_prc		*ft_init_vm_vector_prc(t_vm_vector_prc *v, int init_size);
t_vm_vector_prc* 	ft_vm_vector_prc_cpy(const t_vm_vector_prc *src);
void				ft_free_vm_vector_prc(t_vm_vector_prc **v);
void				ft_free_vm_vector_prc_simple(void *v);
int					ft_free_ret_vm_vector_prc(t_vm_vector_prc **v, int ret);
t_process			*ft_vm_vector_prc_push_back(t_vm_vector_prc **v_ptr);
char				ft_vm_vector_prc_fit(t_vm_vector_prc **v_ptr);

#endif
