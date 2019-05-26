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

char g_unexp_token[] =
"{Bold}{Red}ERROR{eof}  -  Unexpected symbol >>> {\\226}%.1r{eof} <<<\n"
"          >>> {\\226}%c{eof} <<< expected\n";

char g_exp_same_line[] =
"{Bold}{Red}ERROR{eof}  -  Expected {\\226}player-%s{eof} in same line\n";

char g_bad_byte[] =
"{Bold}{Red}ERROR{eof}  -  Bad hex-byte >>> {\\226}%.*s{eof} <<<\n"
"          Need to be 2-digit long (\\xff for example)\n";

char g_pos[] =
"          In {Bold}%s{eof}:{\\202}{Bold}%d{eof}:{Bold}%d{eof}\n";

char g_wrn_too_long[] =
"{Bold}{\\202}WARNING{eof} - {\\226}player-%s{eof} too long. "
"Exceeding part is ignored\n";

char g_wrn_ignored[] =
"{Bold}{\\202}WARNING{eof} - Additional chars after {\\226}player-%s{eof} "
"are ignored\n";

char g_wrn_double[] =
"{Bold}{\\202}WARNING{eof} - Extra appearance of {\\226}player-%s{eof} "
"ignored\n";

char *g_errors[] = {
		g_unexp_token,
		g_exp_same_line,
		g_bad_byte
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