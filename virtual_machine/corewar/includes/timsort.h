/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timsort.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 04:44:00 by ggerardy          #+#    #+#             */
/*   Updated: 2019/08/18 04:44:00 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIMSORT_H
# define TIMSORT_H

void			ft_merge_left(int *data, unsigned int lhs[2],
		unsigned int rhs[2]);

void			ft_merge_right(int *data, unsigned int lhs[2],
		unsigned int rhs[2]);

void			ft_timsort_merge_if_three(unsigned int stack[][2],
		int stack_size, unsigned int const arr_sizes[3], int *data);

void			ft_merge_rest(unsigned int stack[][2],
		int stack_size, unsigned int arr_sizes[3], int *data);

void			ft_merge_if_need(unsigned int stack[][2],
		int stack_size, unsigned int arr_sizes[3], int *data);

#endif
