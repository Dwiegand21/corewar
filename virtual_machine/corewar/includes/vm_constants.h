/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_constants.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 16:55:36 by dwiegand          #+#    #+#             */
/*   Updated: 2019/06/30 16:32:56 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_VIRTUAL_MACHINE_CONSTANTS_H
# define COREWAR_VIRTUAL_MACHINE_CONSTANTS_H

# define INIT_VECTOR_SIZE 256
# define INIT_CARRIAGES_COUNT 4096

/*
**					ERRORS_DEFINES
*/
# define ERR_MANY_ARGS			"Too_many_arguments\n"
# define ERR_READ				"Read file error\n"
# define ERR_OPEN				"Open file error\n"
# define ERR_ALLOC				"Memory allocation error\n"
# define INV_FILE				"Invalid file\n"
# define INV_ARGS				"Invalide arguments\n"
# define INV_CODE_SIZE			"Invalide code size\n"


# define USAGE					"\
Usage: ./corewar [ -dump N | -v ] [ [ -n N ] <champion1.cor> ] ...\n"

/*
**					FLAGS_DEFINES
*/
# define DUMP				1u
# define VISUALIZATION		2u
# define PROCESS_PRINT		4u
# define STEP_DEBUG			8u

# define DISPLAY (area->flags & 0x02)

/*
**					OCTET_OP DEFINES
*/
# define OCT00				((PPC(1) & 0b11000000) >> 6)
# define OCT01				((PPC(1) & 0b00110000) >> 4)
# define OCT02				((PPC(1) & 0b00001100) >> 2)
# define OCT03				((PPC(1) & 0b00000011))

/*
**					CHECK_VALUE DEFINES
*/
# define R_T(x)				(x == REG_CODE)
# define D_T(x) 			(x == DIR_CODE)
# define I_T(x) 			(x == IND_CODE)
# define DI_T(x)			(x == DIR_CODE || x == IND_CODE)
# define RD_T(x)			(x == REG_CODE || x == DIR_CODE)
# define RI_T(x)			(x == REG_CODE || x == IND_CODE)
# define RDI_T(x)			(x == REG_CODE || x == DIR_CODE || x == IND_CODE)

# define IS_REG(x)			(x > 0 && x < 17)

/*
**					OPERATION DEFINES
*/
# define SHIFT(x)			((PC + x) % MEM_SIZE)
# define ISHIFT(x)			((PC + x % IDX_MOD) % MEM_SIZE)

# define PPC(x)				area->map[(PC + x) % MEM_SIZE]
# define PIPC(x)			area->map[(PC + x % IDX_MOD) % MEM_SIZE]
# define PREG(x)			process->reg[x - 1]

/*
**					PROCESS STRUCT DEFINES
*/
# define PC					process->pc
# define SLEEP				process->sleep
# define PLAYER				process->player
# define CARRY				process->carry
# define LIVE_S				process->live_in_session

# define MAP				area->map
# define TIMELINE_SIZE		1001
# define APLAYER(x)			area->players[x]

# define SCYCLE_INROUND		area->g_stats.cycle_in_round
# define SN_CYCLES			area->g_stats.n_cycles
# define SDIE_CYCLE			area->g_stats.cycle_to_die
# define SDIE_CYCLE_DELTA	area->g_stats.cycle_to_die_delta
# define SNOT_CHANGED		area->g_stats.not_changed_checks
# define SLIVES_IN_ROUND	area->g_stats.lives_in_round
# define SDUMP_CYCLE		area->g_stats.cycle_to_dump
# define SN_PLAYERS			area->g_stats.n_players
# define SN_PROCESS			area->g_stats.n_processes

# define PROC_PRINT			"//#/##/:"

# define PRS_KEY(x)			(((t_pair *)(x))->key)
# define PRS_VALUE(x)		((t_process *)(((t_pair *)(x))->value))


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
