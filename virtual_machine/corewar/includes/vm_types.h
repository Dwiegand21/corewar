/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 16:55:36 by dwiegand          #+#    #+#             */
/*   Updated: 2019/06/30 16:32:56 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_VIRTUAL_MACHINE_TYPES_H
# define COREWAR_VIRTUAL_MACHINE_TYPES_H

#include "libft.h"
#include "vm_constants.h"
#include <stdbool.h>
#include <stdint.h>
//#include "vm_vector.h"

typedef struct s_process			t_process;
typedef struct s_player				t_player;
typedef struct s_cor_file			t_cor_file;
typedef struct s_area				t_area;
typedef struct s_ops				t_ops;
typedef struct s_game_condition		t_gcond;

typedef struct	s_vm_vector_int
{
	int			*data;
	int			len;
	int			capacity;
	int			offset;
}				t_vm_vector_int;

typedef struct	s_vm_vector_prc
{
	t_process	*data;
	int			len;
	int			capacity;
	int			offset;
}				t_vm_vector_prc;

struct		s_process
{
	uint32_t		pc;
	uint32_t		sleep;

	int32_t			reg[REG_NUMBER];

	bool			carry;
	int32_t			n_lives;
//	bool			live_in_session;

	uint32_t		ordinal_number;
	uint32_t		player;
	void			(*f)(t_area*, t_process**);
};

struct		s_player
{
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];

	uint32_t		ordinal_number;
	uint32_t		start_pos;

	int32_t			last_live;
	// ...
};

struct		s_cor_file
{
	char			*file_name;
	int32_t			champ_index;

	int32_t			fd;
	int32_t			code_size;
};

struct		s_game_condition
{
	int32_t			cycle_in_round;
	int32_t			n_cycles;
	int32_t			cycle_to_die_delta;
	int32_t			cycle_to_die;
	int32_t			not_changed_checks;

	int32_t			lives_in_round;

	int32_t			cycle_to_dump;

	uint32_t		n_players;
	uint32_t		n_processes;

	uint32_t		next_process_index;

};

struct		s_area
{
	t_vm_vector_prc *carriages;
	uint8_t			*map;
	t_gcond			g_stats;

	t_player		*players;
	t_vm_vector_int		*time;

	uint32_t		flags;
	int32_t			win;

	int32_t			n_die_cycle;

	int32_t			current_index;
};

struct		s_ops
{
	char		name[6];
	int32_t 	sleep;
	void		(*f)(t_area*, t_process**);
};

#endif // COREWAR_VIRTUAL_MACHINE_TYPES_H
