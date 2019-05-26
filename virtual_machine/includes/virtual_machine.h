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
# include <string.h>

/*
**		1. Изменить поведение переменной ' standart_ord_n '.
*/

# define DEBUG_				// Debug mode


void		ft_error(char*	error);		// libft
void		ft_print_endian();			// libft
int 		ft_strnequ_rev(const char *s1, const char *s2, size_t n);
void		bytes_reverse(void *param, size_t size);
void		*ft_memalloc(size_t size);

void		print_map(uint8_t *map);

t_area*		initialization_area(void);
int 		read_arguments(t_area *p, int32_t av, char **ac);

void		free_args(t_area **p);

#endif // COREWAR_VIRTUAL_MACHINE_H
