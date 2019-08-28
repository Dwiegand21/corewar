/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_local.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 18:25:31 by dwiegand          #+#    #+#             */
/*   Updated: 2019/08/28 15:05:28 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_FT_PRINTF_LOCAL_H
# define LIBFT_FT_PRINTF_LOCAL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>
# include "libft.h"

# define RED			"\x1b[31m"
# define GREEN			"\x1b[32m"
# define YELLOW			"\x1b[33m"
# define BLUE			"\x1b[34m"
# define MAGENTA		"\x1b[35m"
# define CYAN			"\x1b[36m"
# define RESET			"\x1b[0m"

# define MODS_N_TYPES	"LjlhidDuUsScCfFoOpxXeEgGbrkbz"
# define ITYPES			"cCdDiuUxXoObp%"
# define FTYPES			"Ffeg"
# define MODS			"Llhjz"
# define TYPES			"idDuUsScCfFoOpxXeEgGbrkb"
# define FLAGS			" +-0#'"

# define HEX			"0123456789abcdef"

# define MAX(x,y)	(x > y) ? (x) : (y)
# define MIN(x,y)	(x < y) ? (x) : (y)
# define ABS(x)		(x < 0) ? -(x) : (x)
# define PLUS(x)	(x == 43) (x) : (0)

typedef float			t_dbl32;
typedef double			t_dbl64;
typedef long double		t_dbl80;

typedef struct	s_bitlld
{
	uint64_t		fraction;
	uint32_t		order : 15;
	uint32_t		sign : 1;
}				t_bitlld;

typedef union	u_lld
{
	t_bitlld		blld;
	t_dbl80			value;
}				t_lld;

typedef struct	s_dblinfo
{
	uint64_t		*ipart;
	uint64_t		*fpart;
	int32_t			ilen;
	int32_t			flen;
	int16_t			order;
	uint64_t		fraction;
}				t_dblinfo;

typedef	struct	s_print_flags
{
	int32_t			minus;
	int32_t			plus;
	int32_t			space;
	int32_t			sharp;
	int32_t			zero;
	int32_t			quote;
}				t_pflags;

typedef struct	s_print_argument
{
	char			type[4];
	char			read;
	int32_t			ntype;

	int64_t			i;
	t_dbl80			f;
	char			*s;
	uint32_t		*ws;
}				t_parg;

typedef struct	s_print_arguments
{
	int32_t			count;
	int32_t			cur;
	t_parg			*arg_list;
}				t_pargs;

typedef struct	s_print_list
{
	char				*original;
	int32_t				original_width;

	t_pflags			flags;
	int32_t				width;
	int32_t				precision;
	char				mod[2];
	char				type;

	int32_t				type_pos;
	int32_t				width_pos;
	int32_t				precision_pos;

	int64_t				i;
	t_dbl80				f;
	char				*s;
	uint32_t			*ws;

	int32_t				len;
	char				*prepared;

	struct s_print_list	*next;
}				t_plist;

typedef struct	s_env
{
	t_plist		*plist;
	t_pargs		*args;
	t_plist		*cur;
	int32_t		dollar;
	int32_t		max_arg_pos;
	int32_t		max_arg_count;
	char		error;
}				t_env;

/* ldlb.c */
uint64_t		minipowu(int32_t nbr, int32_t power);
void			fold_lists(uint64_t *fpart, uint64_t *tpart, int32_t tcur);
void			powup(uint64_t *tpart, int32_t tcur, int32_t power);
void			mod_step(uint64_t *part, int32_t *n);
uint64_t		nbrlen_healper(uint64_t nbr);
int32_t			calculate_fpart(t_dblinfo *dbl, int16_t order);
int32_t			calculate_ipart(t_dblinfo *dbl, int16_t order);
void			round_ldbd_more_healper(t_dblinfo *dbl, int32_t mod);
void			round_ldbd_more(t_dblinfo *dbl, int32_t elem, int32_t pos);
void			round_ldbd_equal(t_dblinfo *dbl, int32_t elem, int32_t pos);
void			round_findrank(t_dblinfo *dbl, int32_t elem, int32_t pos);
int32_t			round_ldbd(t_dblinfo *dbl, int32_t precision);
void			set_nbr(char **array, uint64_t nbr, int32_t range);
void			get_float_prepared_helper(t_dblinfo *dbl,
											int32_t *pec, char **prepared);
char			*get_float_prepared(t_dblinfo *dbl, int32_t pec, int32_t sign);
int32_t			special_values(t_env *env, t_lld *lld);
t_dblinfo		*dblinfo_init(t_bitlld *blld);
int32_t			dblinfo_del(t_dblinfo **dbl, int32_t val);
int32_t			ldbl_process_pre(t_env *env, t_lld lld);
int32_t			ldbl_process(t_env *env);
/* init.c */
t_plist			*create_plist_node(void);
int32_t			args_init(t_env *env, int32_t count, char *format);
int32_t			init_arg_list(t_env *env, va_list *ap);
/* init2.c */
int32_t			ft_printf_init(const char *format, t_env *env);
t_env			*init_env(void);
char			*allocate_buffer(const t_plist *cur);
int				set_to_plist(t_env **env, const char *format, va_list *va);
/* tools.c */
int32_t			char_in_string(char c, char *str);
void			change_prepared(t_env *env, char **tmp, int width);
char			*read_ull(char *str, uint64_t *n);
int32_t			shift_int(char *str, int32_t *n);
int				read_int_to_param(char *c, int *param, int shift);
void			*ft_memcpy(void *dst, const void *src, size_t n);
/* args.c */
void			get_args(t_env *env);
int32_t			arg_cmp(t_pargs *args, int32_t arg_pos, char *mod, char *type);
int32_t			get_args_count(t_env *env, char *format);
/* plist */
void			format_analysis(t_env *env, char *format);
int32_t			format_analysis_expression(t_env *env, char *format);
int				prepare_plist(t_env *env);
char			*get_real_flags(t_plist *cur);
/* main.c */
int32_t			free_printf(t_env *env);
/* ft_vprintf.c */
int				ft_vdprintf(int fd, const char *format, va_list *va);
int				ft_vfprintf(FILE *file, const char *format, va_list *va);
int				ft_vsprintf(char *buf, const char *format, va_list *va);
int				ft_vasprintf(char **buf, const char *format, va_list *va);
/* processing.c */
int				dbl_processing(t_env *env);
int				int_processing(t_env *env);
int				str_processing(t_env *env);
/* preprocessing.c */
int				pre_char(t_env *env);
int				pre_int(t_env *env);
int				pre_hex(t_env *env);
int				pre_bin(t_env *env);
/* postprocessing.c */
int				post_str(t_env *env);
int				post_char(t_env *env);
int				post_int(t_env *env);
int				post_hex(t_env *env);
int				post_bin(t_env *env);
int				post_float(t_env *env);
/* checkers.c */
int32_t			is_type_pos(char *c, t_env *env);
int32_t			is_flag(char c, t_plist *cur);
int32_t			is_width(char *c, t_env *env);
int32_t			is_precision(char *c, t_env *env);
int32_t			is_modifier(char *c, t_plist *cur);
int32_t			is_type(char c, t_env *env);
/* floats */
int32_t			ldbl_process(t_env *env);
/* validation.c */
int				check_valid_format(char *format, t_env *env);

int				octal_base(t_env *env, uint64_t nbr);
int				hex_base(t_env *env, uint64_t nbr, int32_t type);

int32_t			char_in_string(char c, char *str);
int32_t			is_color(char *c, t_plist *cur);

int32_t			is_arg_pos(char *str, int32_t *res);
int				llitoa(t_plist *cur, uint64_t nbr, int32_t sign);
void			itoa_base(t_env *env, int32_t base, int32_t type);
int				dectobin(t_plist *cur, uint64_t nbr, uint32_t size);
int				dectobin_sharp(t_plist *cur, uint64_t nbr, uint32_t size);
void			ldbltoa(t_plist *cur, t_dbl80 nbr, int32_t sign);
int				lstr_tramsformation(t_env *env, uint32_t *str);
int				str_transformation(t_plist *cur, char *str);
int				wchar_transformation(t_env *env, uint32_t c);
/* wchar_tools.c */
uint32_t		*wstrdup(uint32_t *str, uint32_t n);
uint32_t		wstr_len(uint32_t *array);
void			wstr_cpy(char *str, uint32_t *array, uint32_t n);
/* uni_encode.c */
void			wstr_encode(uint32_t *array);
uint32_t		wchar_encode(uint32_t c);

/*Healper*/
int32_t			m_func(char *str);
void			print_bits_helper(void *str, int32_t count);

/* print_result.c */
int				print_result_fd(t_plist *cur, int fd);
int				print_result_str(t_plist *cur, char *buff);
int				print_result_file(t_plist *cur, FILE *file);

/* free_printf.c */
int				free_printf(t_env *env);

#endif
