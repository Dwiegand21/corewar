/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 19:44:00 by ggerardy          #+#    #+#             */
/*   Updated: 2019/05/25 19:44:00 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char g_unexp_token[] =
"{Bold}{Red}ERROR{eof}  -  Unexpected symbol >>> {\\226}%.1r{eof} <<<\n"
"          >>> {\\226}%c{eof} <<< expected\n";
char g_exp_same_line[] =
"{Bold}{Red}ERROR{eof}  -  Expected {\\226}player-%s{eof} in same line\n";
char g_bad_byte[] =
"{Bold}{Red}ERROR{eof}  -  Bad hex-byte >>> {\\226}%.*s{eof} <<<\n"
"          Need to be 2-digit long (\\xff for example)\n";
char g_missing_param[] =
"{Bold}{Red}ERROR{eof}  -  Missing {\\226}player-%s{eof}\n";
char g_wrong_char_lbl[] =
"{Bold}{Red}ERROR{eof}  -  Wrong character >>> {\\226}%.1r{eof} <<<\n"
"          In label >>> {\\226}%s{eof} <<<\n";
char g_miss_lbl_chr[] =
"{Bold}{Red}ERROR{eof}  -  Missing label-character >>> {\\226}%c{eof} <<<\n"
"          After label >>> {\\226}%s{eof} <<<\n";
char g_mult_label[] =
"{Bold}{Red}ERROR{eof}  -  Multiple definition of label "
">>> {\\226}%s{eof} <<<\n";
char g_bad_cmd[] =
"{Bold}{Red}ERROR{eof}  -  Invalid operation >>> {\\226}%.*s{eof} <<<\n";
char g_bad_arg[] =
"{Bold}{Red}ERROR{eof}  -  Invalid argument value >>> {\\226}%.*s{eof} <<<\n";
char g_bad_reg_idx[] =
"{Bold}{Red}ERROR{eof}  -  Invalid register index >>> {\\226}%.*s{eof} <<<\n";
char g_bad_arg_count[] =
"{Bold}{Red}ERROR{eof}  -  Wrong number of arguments for command "
">>> {\\226}%s{eof} <<<\n"
"          Expected {\\226}%d{eof}, but {\\226}%d{eof} got\n";
char g_missing_sep[] =
"{Bold}{Red}ERROR{eof}  -  Missing separator ({\\226}%c{eof})\n";
char g_extra_sep[] =
"{Bold}{Red}ERROR{eof}  -  Extra separator ({\\226}%c{eof})\n";
char g_miss_arg_aft_prfx[] = // todo print 'for command'
"{Bold}{Red}ERROR{eof}  -  Missing argument after prefix "
">>> {\\226}%.*s{eof} <<<\n";
char g_miss_arg[] = // todo print 'for command'
"{Bold}{Red}ERROR{eof}  -  Missing argument\n";

char g_wrn_too_long[] =
"{Bold}{\\202}WARNING{eof} - {\\226}player-%s{eof} too long. "
"Exceeding part is ignored\n";
char g_wrn_ignored[] =
"{Bold}{\\202}WARNING{eof} - Additional chars after {\\226}player-%s{eof} "
"are ignored\n";
char g_wrn_double[] =
"{Bold}{\\202}WARNING{eof} - Extra appearance of {\\226}player-%s{eof} "
"ignored\n";

char g_pos[] =
"          In {Bold}%s{eof}:{\\202}{Bold}%d{eof}:{Bold}%d{eof}\n";
char g_pos_before[] =
"          Before {Bold}%s{eof}:{\\202}{Bold}%d{eof}:{Bold}%d{eof}\n";

char *g_errors[] = {
		g_unexp_token,
		g_exp_same_line,
		g_bad_byte,
		g_missing_param,
		g_wrong_char_lbl,
		g_miss_lbl_chr,
		g_mult_label,
		g_bad_cmd,
		g_bad_arg,
		g_bad_reg_idx,
		g_bad_arg_count,
		g_missing_sep,
		g_extra_sep,
		g_miss_arg_aft_prfx,
		g_miss_arg,
};

char g_chars[] = {
		'\r',
		'\t',
		'\a',
		'\f',
		'\v',
		'\b',
		'\n',
		'\"',
		'\'',
		'\?',
		'\\',
};

char g_backslash_literals[] = "rtafvbn\"\'\?\\";

t_op g_functions[16] = {
	{"live",
		{T_DIR, 0, 0}, 0, 0, 4, 1},
	{"ld",
		{T_DIR | T_IND, T_REG, 0}, 1, 0, 2, 2},
	{"st",
		{T_REG, T_REG | T_IND, 0}, 1, 0, 2, 2},
	{"add",
		{T_REG, T_REG, T_REG}, 1, 0, 3, 3},
	{"sub",
		{T_REG, T_REG, T_REG}, 1, 0, 3, 3},
	{"and",
		{T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG}, 1, 0, 3, 3},
	{"or",
		{T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG}, 1, 0, 2, 3},
	{"xor",
		{T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG}, 1, 0, 3, 3},
	{"zjmp",
		{T_DIR, 0, 0}, 0, 1, 4, 1},
	{"ldi",
		{T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG}, 1, 1, 3, 3},
	{"sti",
		{T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR}, 1, 1, 3, 3},
	{"fork",
		{T_DIR, 0, 0}, 0, 1, 4, 1},
	{"lld",
		{T_DIR | T_IND, T_REG, 0}, 1, 0, 3, 2},
	{"lldi",
		{T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG}, 1, 1, 4, 3},
	{"lfork",
		{T_DIR, 0, 0}, 0, 1, 5, 1},
	{"aff",
		{T_REG, 0, 0}, 1, 0, 3, 1}
};
