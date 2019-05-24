/* ************************************************************************** */
/*                                                                            */
/*                                                            ::: ::::::::    */
/*    asm.h                                              :+: :+: :+:          */
/*                                                             +:+ +:+ +:+    */
/*    By: ggerardy <marvin@42.fr>                    +#+ +:+ +#+              */
/*                                                         +#+#+#+#+#+ +#+    */
/*    Created: 2019/05/24 09:28:00 by ggerardy          #+# #+#               */
/*    Updated: 2019/05/24 09:28:00 by ggerardy         ### ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"

# define IND_SIZE 2
# define REG_SIZE 4
# define DIR_SIZE REG_SIZE

# define REG_CODE 1
# define DIR_CODE 2
# define IND_CODE 3

# define MAX_ARGS_NUMBER 4
# define MAX_PLAYERS 4
# define MEM_SIZE (4*1024)
# define IDX_MOD (MEM_SIZE / 8)
# define CHAMP_MAX_SIZE (MEM_SIZE / 6)

# define COMMENT_CHAR '#'
# define LABEL_CHAR ':'
# define DIRECT_CHAR '%'
# define SEPARATOR_CHAR ','

# define LABEL_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING ".name"
# define COMMENT_CMD_STRING ".comment"

# define REG_NUMBER 16

# define CYCLE_TO_DIE 1536
# define CYCLE_DELTA 50
# define NBR_LIVE    21
# define MAX_CHECKS  10

# define T_REG 1
# define T_DIR 2
# define T_IND 4
# define T_LAB 8

# define PROG_NAME_LENGTH (128)
# define COMMENT_LENGTH (2048)
# define COREWAR_EXEC_MAGIC 0xea83f3

# define TOKENIZE()

typedef enum 			e_token_type {
	LBL = 0,   /// label (char*)
	LC = 1,   /// label_char (char)
	OP = 2,  /// operation (char)
	T = 3,  /// type (char)
	D = 4, /// delimiter (char)
	A = 5 /// argument (unsigned int)
}						t_token_type;

typedef struct			s_token
{
	t_token_type	type;
	void			*carry;
}						t_token;

typedef struct			s_champ
{
	char 			name[PROG_NAME_LENGTH + 1];
	unsigned int	size;
	char 			comment[COMMENT_LENGTH + 1];
	unsigned char	*exec;
	t_vector		*tokens;
}						t_champ;

#endif
