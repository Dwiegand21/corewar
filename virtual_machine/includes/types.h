/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 16:55:36 by dwiegand          #+#    #+#             */
/*   Updated: 2019/05/29 17:23:41 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_VIRTUAL_MACHINE_TYPES_H
# define COREWAR_VIRTUAL_MACHINE_TYPES_H

typedef struct s_process	t_process;
typedef struct s_player		t_player;
typedef struct s_cor_file	t_cor_file;
typedef struct s_area		t_area;
typedef struct s_ops		t_ops;

enum		e_player_pos {FIRST, SECOND, THIRD, FOURTH};

struct		s_process
{
	uint8_t			*addr;
	int32_t			sleep;

	int32_t			reg[REG_NUMBER];

	bool			carry;
	bool			live_in_session;

	uint32_t		player;

	t_process		*next;
};

struct		s_player
{
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];

	uint32_t		ordinal_number;
	uint32_t		start_pos;

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
	int32_t			round;
	int32_t			cycle_step;
	int32_t			cycle_to_die;

	int32_t			lives_in_round;

	int32_t			dump_round;

	uint8_t			*map;

	int32_t			n_players;
	int32_t			n_processes;

	t_player		*players;
	t_process		*processes;

	uint32_t		flags;
};

struct		s_ops
{
	char		name[6];
	int32_t 	sleep;
	void		(*func)(t_area*, t_process*);
};

#endif // COREWAR_VIRTUAL_MACHINE_TYPES_H