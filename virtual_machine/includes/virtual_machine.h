/* ************************************************************************** */
/*                                                                            */
/*                                                            ::: ::::::::    */
/*    virtual_machine.h                                  :+: :+: :+:          */
/*                                                             +:+ +:+ +:+    */
/*    By: dwiegand <marvin@42.fr>                    +#+ +:+ +#+              */
/*                                                         +#+#+#+#+#+ +#+    */
/*    Created: 2019/05/24 08:22:24 by dwiegand          #+# #+#               */
/*    Updated: 2019/05/24 08:22:24 by dwiegand         ### ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_VIRTUAL_MACHINE_H
# define COREWAR_VIRTUAL_MACHINE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>

# include <fcntl.h>
# include <sys/types.h>

# include "constants.h"
# include "types.h"
# include "libft.h"

/*
**		1. Изменить поведение переменной ' standart_ord_n '.
*/

# define DEBUG_				// Debug mode
//# define DEBUG_MAP_

void		ft_error(char*	error);		// libft
void		ft_print_endian();			// libft
void		bytes_reverse(void *param, size_t size);

void		print_map(uint8_t *map);

t_area*		initialization_area(void);
int 		read_arguments(t_area *p, int32_t av, char **ac);

int 		initialization_players(t_area *area, t_cor_file *files);

void		free_args(t_area **p);
int32_t 	is_integer(const char *str, int32_t* nbr);
/*
**		check_flags.c
*/
int32_t		check_flags(int32_t *av, char ***ac, int32_t *dump);

#endif // COREWAR_VIRTUAL_MACHINE_H
