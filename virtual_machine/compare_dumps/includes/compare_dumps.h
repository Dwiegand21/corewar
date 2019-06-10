/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_dumps.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 05:09:16 by axtazy            #+#    #+#             */
/*   Updated: 2019/06/07 13:08:39 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIRTUAL_MACHINE_DUMP_DIFF_H
#define VIRTUAL_MACHINE_DUMP_DIFF_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdint.h>
# include "libft.h"

# define BUFF_SIZE			256

# define RESET				"\033[0m"
# define RED				"\033[1;91m"
# define GREEN				"\033[1;92m"
# define W_BRED				"\033[1;101m"
# define W_BGREEN			"\033[1;102m"
# define W_BYELLOW			"\033[1;103m"

# define PROC_PRINT			"\x3f\x9a\x1c\xae"

typedef struct s_output		t_output;
typedef struct s_dump_diff	t_dump;

struct		s_output
{
	char*		origin;
	char* 		our;
};

struct		s_dump_diff
{
	t_output*	strings;
	FILE*		origin_vm;
	FILE*		our_vm;
};

int 			read_processes_output(t_dump *dd, char *av[]);

int				compare_output(t_dump *dd);

#endif //VIRTUAL_MACHINE_DUMP_DIFF_H
