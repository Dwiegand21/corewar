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

char errors[][] = {
	"{Bold}{Red}ERROR{eof} - Unexpected token >>> {\\226}%.1r{eof} <<<\n"
 	"        In {\\202}%d{eof}:%d\n"
	"        >>> {Green}%c{eof} <<< expected\n",
	"{Bold}{Red}ERROR{eof} - Expected {\\226}%s{eof} in same line\n"
	"        In {\\202}%d{eof}:%d\n"
}