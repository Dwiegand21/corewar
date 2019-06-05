/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 16:55:36 by dwiegand          #+#    #+#             */
/*   Updated: 2019/06/05 17:08:16 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_VIRTUAL_MACHINE_TYPES_H
# define COREWAR_VIRTUAL_MACHINE_TYPES_H



#include "libft.h"
#include "vm_constants.h"

typedef struct s_process	t_process;
typedef struct s_player		t_player;
typedef struct s_cor_file	t_cor_file;
typedef struct s_area		t_area;
typedef struct s_ops		t_ops;
typedef struct s_rer		t_rer;

enum		e_player_pos {FIRST, SECOND, THIRD, FOURTH};

struct		s_rer
{
	int a;
};

struct		s_process
{
	uint32_t		pc;
	uint32_t		sleep;

	int32_t			reg[REG_NUMBER];

	bool			carry;
	bool			live_in_session;

	uint32_t		player;
	void			(*f)(t_area*, t_process*);

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

struct		s_area
{
	uint32_t		round;
	uint32_t		cycle_step;
	uint32_t		cycle_to_die;

	int32_t			lives_in_round;

	int32_t			dump_round;

	uint8_t			*map;

	uint32_t		n_players;
	uint32_t		n_processes;

	t_player		*players;
	t_list			*processes;

	uint32_t		flags;
};

struct		s_ops
{
	char		name[6];
	int32_t 	sleep;
	void		(*f)(t_area*, t_process*);
};

#endif // COREWAR_VIRTUAL_MACHINE_TYPES_H
