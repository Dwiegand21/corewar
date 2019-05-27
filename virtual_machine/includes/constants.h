
#ifndef COREWAR_VIRTUAL_MACHINE_CONSTANTS_H
# define COREWAR_VIRTUAL_MACHINE_CONSTANTS_H

//# define PROJECT_NAME			"corewar"

/*
**					ERRORS_DEFINES
*/
# define ERR_MANY_ARGS			"Too_many_arguments\n"
# define ERR_FILE 				"File doesn't exist\n"
# define ERR_READ				"Read file error\n"
# define ERR_OPEN				"Open file error\n"
# define ERR_ALLOC				"Memory allocation error\n"
# define INV_FILE				"Invalid file\n"
# define INV_ARGS				"Invalide arguments\n"
# define INV_CODE_SIZE			"Invalide code size\n"

/*
**					FLAGS_DEFINES
*/
# define DUMP					1
# define VISUALIZATION			2

# define DISPLAY (area->flags & 0x02)

/*
**					OCTET_OP_DEFINES
*/
# define OCT1(x)	(x & 0xFF)
# define OCT2(x)	((x >> 4) & 0xFF)
# define OCT3(x)	((x >> 8) & 0xFF)
# define OCT4(x)	((x >> 12) & 0xFF)

/*
**					OP.H DEFINES
*/
# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_PLAYERS			4

# define MEM_SIZE				(4 * 1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

# define REG 					1
# define DIR 					4
# define IND 					2

# define T_REG					1
# define T_DIR					2
# define T_IND					4

# define PROG_NAME_LENGTH		128
# define COMMENT_LENGTH			2048
# define COREWAR_EXEC_MAGIC		0xea83f3


#endif // COREWAR_VIRTUAL_MACHINE_CONSTANTS_H


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
