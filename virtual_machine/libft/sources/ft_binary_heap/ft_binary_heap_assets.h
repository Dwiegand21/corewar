/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binary_heap_assets.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 16:52:53 by dwiegand          #+#    #+#             */
/*   Updated: 2019/07/04 17:41:22 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_FT_BINARY_HEAP_ASSETS_H
# define LIBFT_FT_BINARY_HEAP_ASSETS_H

# include "ft_binary_heap.h"
# include "../ft_vector/ft_vector_assets.h"
# include "ft_project_assets.h"
# include "ft_memory.h"

# define PARENT(x)		((x - 1) / 2)
# define LEFT(x)		(x * 2 + 1)
# define RIGHT(x)		(x * 2 + 2)

void			ft_bheap_swap(void **p1, void **p2);

#endif
