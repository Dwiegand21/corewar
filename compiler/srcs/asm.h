/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapka                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 18:49:51 by ggerardy          #+#    #+#             */
/*   Updated: 2019/05/29 18:49:51 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "fcntl.h"
# include "libft.h"
# include "asm.h"
# include "stdint.h"
# include "zconf.h"

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
# define T_REG 1u
# define T_DIR 2u
# define T_IND 4u
# define T_LAB 8u
# define PROG_NAME_LENGTH (128)
# define COMMENT_LENGTH (2048)
# define COREWAR_EXEC_MAGIC 0xea83f3
# define GET_DATA(p) (((size_t)(p) << 3u) >> 3u)
# define GET_TYPE(p) ((t_token_type)((size_t)(p) >> 61u))
# define BUFF_SIZE 4096

typedef struct	s_op
{
	char			name[5];
	uint8_t			arg[3];
	uint8_t			need_types_byte;
	uint8_t			short_dir;
	int				namelen;
}				t_op;

typedef enum	e_error
{
	UNEXP_TOKEN = 0,
	SAME_LINE_EXP = 1,
	BAD_BYTE = 2,
	MISSING_PARAM = 3,
	WRONG_CHAR_LBL = 4,
	MISS_LBL_CHAR = 5,
	MULT_LABEL = 6,
	BAD_CMD = 7
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

typedef struct	s_cmd
{
	unsigned char	cmd;
	unsigned char	arg_types[3];
	void			*args[3];
	int				address;
}				t_cmd;

typedef struct	s_champ
{
	t_string		*name;
	unsigned int	size;
	t_string		*comment;
	t_string		*exec;
	t_vector		*cmds;
	char			*curr_line;
	int				line;
	char			*file;
	int				fd;
	int				error_count;
	t_map			*labels;
	t_vector		*current_labels;
	int				address;
}				t_champ;

extern char		g_wrn_ignored[];
extern char		g_pos_before[];
extern char		g_missing_param[];
extern char		g_unexp_token[];
extern char		g_backslash_literals[];
extern char		g_wrong_char_lbl[];
extern char		g_mult_label[];
extern char		g_wrn_too_long[];
extern char		g_miss_lbl_chr[];
extern char		g_wrn_double[];
extern t_op		g_functions[16];
extern char		g_exp_same_line[];
extern char		g_pos[];
extern char		g_bad_byte[];
extern char		*g_errors[];
extern char		g_bad_cmd[];
extern char		g_chars[];

/*
**ft_champ.c
*/
int				ft_free_champ(t_champ **champ, int ret);
t_champ			*ft_make_champ(char *file, int fd);
void			ft_champ_upd_line(t_champ *champ, char *line);
/*
**ft_header_utils.c
*/
void			ft_parse_byte(char **ln, t_string **res, t_champ *champ);
void			ft_parse_backslash(char **ln, t_string **res,
			t_champ *champ);
int				ft_check_empty_string(char *ln, t_champ *champ,
			t_token_type type);
void			ft_skip_line(char *ln, int *qoute_count);
void			ft_skip_string(t_champ *champ, char *ln);
/*
**ft_parse_header.c
*/
void			ft_parse_header(t_champ *champ, int fd);
void			ft_parse_name_comment(t_champ *champ, char *ln,
			t_token_type type);
int				ft_validate_string(t_champ *champ, char **ln,
			t_token_type type);
void			ft_parse_string(char *ln, t_string **res, t_token_type type,
			t_champ *champ);
int				ft_get_data_from_line(char *ln, t_string **res,
			t_token_type type, t_champ *chmp);
/*
**ft_utils.c
*/
void			ft_make_error(t_error type, t_champ *champ, int pos,
			void *args[4]);
void			*tokenize(t_token_type type, void *carry);
void			ft_check_exist_name_cmt(t_champ *champ);
/*
**parser.c
*/
char			*ft_get_lbl_name(t_champ *champ, char **s);
int				ft_is_command(char *line);
void			ft_parse_arg(t_champ *champ, t_cmd *cmd, char **ln);
void			ft_parse_command(t_champ *champ, char *ln, int cmd_num);
size_t			ft_find_bad_cmd_len(char *ln);
void			ft_add_label(t_champ *champ, char *lbl, char *ln);
void			ft_parse_label(t_champ *champ, char *ln);
void			ft_parse_line(t_champ *champ, char *ln);
void			ft_parse_exec(t_champ *champ, int fd);
t_champ			*ft_parser(char *file);
#endif
