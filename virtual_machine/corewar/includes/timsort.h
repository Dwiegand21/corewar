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

void			ft_timsort_merge_if_three(t_timsort_rng *stack,
		int stack_size,
		const unsigned int *arr_sizes,
		int *data);

void			ft_merge_rest(t_timsort_rng *stack,
		int stack_size, unsigned int *arr_sizes, int *data);

int				ft_merge_if_need(t_timsort_rng *stack,
		int stack_size, unsigned int *arr_sizes, int *data);

#endif
