/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 16:55:36 by dwiegand          #+#    #+#             */
/*   Updated: 2019/06/12 13:11:31 by dwiegand         ###   ########.fr       */
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

# include <fcntl.h>
# include <sys/types.h>

# include "vm_constants.h"
# include "vm_types.h"
# include "libft.h"
# include "vm_vector.h"

extern t_ops			g_ops[19];
extern t_vm_vector_int	g_sort_buffer;
extern t_vm_vector_rng	g_sort_ranges;
extern char				g_usage[];

/*
**		timsort.c
*/
void		ft_timsort_int(int *data, unsigned int ref_len);

/*
**		helpers.c
*/
void		bytes_reverse(void *param, size_t size);
void		winner(t_area *area);

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
void		free_args(t_area *p);

/*
**		check_flags.c
*/
int32_t		is_integer(const char *str, int32_t *nbr);
int32_t		check_flags(int32_t *av, char ***ac, int32_t *dump);

/*
**		processes_ops.c
*/
void		new_process(t_area *area, t_process *parent, uint32_t pc);
void		load_process(t_area *area, int32_t player, uint32_t pc);
int32_t		delete_not_live_processes(t_area *area);

/*
**		vm_operations1.c
*/
void		get_op(t_area *area, t_process **carr);
void		next_op(t_area *area, t_process **carr);
void		live_op(t_area *area, t_process **carr);
void		ld_op(t_area *area, t_process **carr);
void		st_op(t_area *area, t_process **carr);
void		add_op(t_area *area, t_process **carr);

/*
**		vm_operations2.c
*/
void		sub_op(t_area *area, t_process **carr);
void		and_op(t_area *area, t_process **carr);
void		or_op(t_area *area, t_process **carr);
void		xor_op(t_area *area, t_process **carr);
void		zjmp_op(t_area *area, t_process **carr);

/*
**		vm_operations3.c
*/
void		ldi_op(t_area *area, t_process **carr);
void		sti_op(t_area *area, t_process **carr);
void		fork_op(t_area *area, t_process **carr);
void		lld_op(t_area *area, t_process **carr);
void		lldi_op(t_area *area, t_process **carr);

/*
**		vm_operations4.c
*/
void		lfork_op(t_area *area, t_process **carr);
void		aff_op(t_area *area, t_process **carr);

/*
**		vm_ops_methods.c
*/
uint32_t	shift_size(uint8_t arg_byte, int32_t arg_n, uint32_t dir_size);
int32_t		get_argument(t_area *area, t_process *process,
		uint32_t *shift, uint8_t type);
int32_t		get_argument2(t_area *area, t_process *process,
		uint32_t *shift, uint8_t type);
int			check_registers(t_area *area, t_process *process, int32_t n_args,
		int32_t dir_size);
/*
**		vm_map_ops.c
*/
int32_t		get32(t_area *area, t_process *process, uint32_t shift);
int16_t		get16(t_area *area, t_process *process, uint32_t shift);
void		set32(t_area *area,
		t_process *process, uint32_t shift, int32_t value);

/*
**		vm_game.c
*/
int32_t		play_game(t_area *area);

void		print_dump(t_area *area);

#endif
