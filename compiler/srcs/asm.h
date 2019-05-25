/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapka                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 22:47:46 by ggerardy          #+#    #+#             */
/*   Updated: 2019/05/25 22:47:46 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
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
# define NBR_LIVE	21
# define MAX_CHECKS  10
# define T_REG 1
# define T_DIR 2
# define T_IND 4
# define T_LAB 8
# define PROG_NAME_LENGTH (128)
# define COMMENT_LENGTH (2048)
# define COREWAR_EXEC_MAGIC 0xea83f3
# define GET_DATA(p) (((size_t)(p) << 3u) >> 3u)
# define GET_TYPE(p) ((t_token_type)((size_t)(p) >> 61u))
# define BUFF_SIZE 4096

# include "fcntl.h"
# include "libft.h"
# include "asm.h"
# include "zconf.h"

extern char		g_unexp_token[];
extern char		g_backslash_literals[];
extern char		g_bad_byte[];
extern char		g_exp_same_line[];
extern char		g_pos[];
extern char		*g_errors[];
extern char		g_chars[];



typedef enum	e_error
{
	UNEXP_TOKEN = 0,
	SAME_LINE_EXP = 1,
	BAD_BYTE = 3,
}				t_error;

typedef enum	e_token_type
{
	LBL = 0,
	LC = 1,
	OP = 2,
	T = 3,
	D = 4,
	A = 5,
	NAME = 6,
	COMMENT = 7
}				t_token_type;

typedef struct	s_token
{
	t_token_type	type;
	void			*carry;
}				t_token;

typedef struct	s_champ
{
	t_string		*name;
	unsigned int	size;
	t_string		*comment;
	t_string		*exec;
	t_vector		*tokens;
	t_vector		*errors;
	char			*curr_line;
	int				line;
	char			*file;
}				t_champ;

/*
**ft_utils.c
*/
int				ft_free_champ(t_champ **champ, int ret);
t_champ			*ft_make_champ(char *file);
void			ft_make_error(t_error type, t_champ *champ, int pos,
			void* args[4]);
void			*tokenize(t_token_type type, void *carry);
/*
**parser.c
*/
int				ft_validate_string(t_champ *champ, const char *ln,
			t_token_type type);
void			ft_parse_byte(char **ln, t_string **res, t_champ *champ);
void			ft_parse_backslash(char **ln, t_string **res,
			t_champ *champ);
void			ft_get_data_from_line(char *ln, t_string **res,
			t_token_type type, t_champ *champ);
char			*ft_parse_string(char *ln, t_string **res,
			t_token_type type);
int				ft_parse_name_comment(t_champ *champ, const char *ln,
			t_token_type type);
int				ft_parse_name(t_champ *champ, int fd);
t_champ			*ft_parser(char *file);
#endif
