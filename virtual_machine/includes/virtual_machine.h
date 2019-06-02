/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 16:55:36 by dwiegand          #+#    #+#             */
/*   Updated: 2019/06/02 06:35:27 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_VIRTUAL_MACHINE_H
# define COREWAR_VIRTUAL_MACHINE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>
# include <limits.h>
//# include <types.h>

# include <fcntl.h>
# include <sys/types.h>

# include "constants.h"
# include "types.h"
# include "libft.h"

# include <ncurses.h>		// ???

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
**		initialization.c
*/
t_area		*initialization_area(void);

/*
**		read_arguments.c
*/
int			read_arguments(t_area *p, int32_t av, char **ac);

/*
**		read_files.c
*/
int			initialization_players(t_area *area, t_cor_file *files);

/*
**		free_args.c
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
t_process*	start_node(uint32_t pc, int player_i);
void		push_node(t_process **root, t_process *new);

/*
**		vm_methods_and.c
*/
void		and_method1(t_area *area, t_process *process);
void		and_method2(t_area *area, t_process *process);
void		and_method3(t_area *area, t_process *process);

/*
**		vm_methods_or.c
*/
void		or_method1(t_area *area, t_process *process);
void		or_method2(t_area *area, t_process *process);
void		or_method3(t_area *area, t_process *process);

/*
**		vm_methods_xor.c
*/
void		xor_method1(t_area *area, t_process *process);
void		xor_method2(t_area *area, t_process *process);
void		xor_method3(t_area *area, t_process *process);

/*
**		vm_operations1.c
*/
void		next_op(t_area *area, t_process *process);
void		live_op(t_area *area, t_process *process);
void		ld_op(t_area *area, t_process *process);
void		st_op(t_area *area, t_process *process);
void		add_op(t_area *area, t_process *process);

/*
**		vm_operations2.c
*/
void		sub_op(t_area *area, t_process *process);
void		and_op(t_area *area, t_process *process);
void		or_op(t_area *area, t_process *process);
void		xor_op(t_area *area, t_process *process);
void		zjmp_op(t_area *area, t_process *process);

/*
**		vm_operations3.c
*/
void		ldi_op(t_area *area, t_process *process);
void		sti_op(t_area *area, t_process *process);
void		fork_op(t_area *area, t_process *process);
void		lld_op(t_area *area, t_process *process);
void		lldi_op(t_area *area, t_process *process);

/*
**		vm_operations4.c
*/
void		lfork_op(t_area *area, t_process *process);
void		aff_op(t_area *area, t_process *process);

/*
**		bigendian_ops.c
*/
int32_t		be_get32(void *p);
int16_t		be_get16(void *p);
void		be_set32(void *p, int32_t value);
void		be_set16(void *p, int16_t value);

#endif // COREWAR_VIRTUAL_MACHINE_H
