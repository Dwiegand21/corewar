/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 16:55:36 by dwiegand          #+#    #+#             */
/*   Updated: 2019/05/27 16:55:36 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_VIRTUAL_MACHINE_H
# define COREWAR_VIRTUAL_MACHINE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>

# include <fcntl.h>
# include <sys/types.h>

# include "constants.h"
# include "types.h"
# include "libft.h"

/*
**		1. Изменить поведение переменной ' standart_ord_n '.
*/
# define DEBUG_			1			// Debug mode
# define DEBUG_MAP_ 	0			// Print map

/*
**		helpers.c
*/
void		ft_error(char *error);
void		ft_print_endian();
void		bytes_reverse(void *param, size_t size);
void		print_map(uint8_t *map);

/*
//		initialization.c
*/
t_area		*initialization_area(void);

/*
//		read_arguments.c
*/
int			read_arguments(t_area *p, int32_t av, char **ac);

/*
//		read_files.c
*/
int			initialization_players(t_area *area, t_cor_file *files);

/*
//		free_args.c
*/
void		free_args(t_area **p);

/*
**		check_flags.c
*/
int32_t		is_integer(const char *str, int32_t *nbr);
int32_t		check_flags(int32_t *av, char ***ac, int32_t *dump);

/*
**		node_ops.c
*/
t_process*	start_node(uint8_t *addr, int player_i);
void		push_node(t_process **root, t_process *new);

#endif // COREWAR_VIRTUAL_MACHINE_H
