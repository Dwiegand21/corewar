/* ************************************************************************** */
/*                                                                            */
/*                                                            ::: ::::::::    */
/*    errors.c                                           :+: :+: :+:          */
/*                                                             +:+ +:+ +:+    */
/*    By: ggerardy <marvin@42.fr>                    +#+ +:+ +#+              */
/*                                                         +#+#+#+#+#+ +#+    */
/*    Created: 2019/05/24 14:46:53 by ggerardy          #+# #+#               */
/*    Updated: 2019/05/24 14:46:53 by ggerardy         ### ########.fr        */
/*                                                                            */
/* ************************************************************************** */

char g_unexp_token[] =
"{Bold}{Red}ERROR{eof} - Unexpected token >>> {\\226}%.1r{eof} <<<\n"
"        In {Bold}%s{eof}:{\\202}{Bold}%d{eof}:{Bold}%d{eof}\n"
"        >>> {Green}%c{eof} <<< expected\n";

char g_exp_same_line[] =
"{Bold}{Red}ERROR{eof} - Expected {\\226}%s{eof} in same line\n"
"        In {Bold}%s{eof}:{\\202}{Bold}%d{eof}:{Bold}%d{eof}\n";

char *g_errors[] = {
		g_unexp_token,
		g_exp_same_line
};