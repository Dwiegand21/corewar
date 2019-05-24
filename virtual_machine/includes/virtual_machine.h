/* ************************************************************************** */
/*                                                                            */
/*                                                            ::: ::::::::    */
/*    virtual_machine.h                                  :+: :+: :+:          */
/*                                                             +:+ +:+ +:+    */
/*    By: dwiegand <marvin@42.fr>                    +#+ +:+ +#+              */
/*                                                         +#+#+#+#+#+ +#+    */
/*    Created: 2019/05/24 08:22:24 by dwiegand          #+# #+#               */
/*    Updated: 2019/05/24 08:22:24 by dwiegand         ### ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_VIRTUAL_MACHINE_H
# define COREWAR_VIRTUAL_MACHINE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE


# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3


# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4 * 1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)


# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


typedef char	t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3


typedef struct	header_s
{
    uint32_t		magic;
    int8_t			prog_name[PROG_NAME_LENGTH + 1];
    uint32_t		prog_size;
    int8_t			comment[COMMENT_LENGTH + 1];
}				header_t;


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


typedef struct	s_node
{
    uint8_t*		addr;
    int32_t			sleep;

	bool			carry;
    bool			live_in_session;

    struct s_node	*next;
}				t_node;

typedef struct	s_area
{
	int32_t			round;
	int32_t			cycle_step;
	int32_t			cycle_to_die;

	t_node*			registrs;
	uint8_t*		map;

}				t_area;

struct			s_info
{
    int8_t			name[15];
    int32_t			stepsForDoing;
    bool			carry_change;
};


t_area*		initialisation_area(int av, char** ac);

#endif // COREWAR_VIRTUAL_MACHINE_H


/*

t_op    op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},

	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},

	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},

	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},

	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},

	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},

	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},

	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},

	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},

	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},

	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},

	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},

	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},

	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},

	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},

	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},

	{0, 0, {0}, 0, 0, 0, 0, 0}
};

*/
