#include "virtual_machine.h"
#include <unistd.h>

void	ft_error(char*	error)
{
	int 	length;

//	if (PROJECT_NAME[0] != 0)
//	{
//		length = 0;
//		while (PROJECT_NAME[length])
//			length++;
//		write(2, PROJECT_NAME, length);
//		write(2, ": ", 2);
//	}
	length = 0;
	while (error[length])
		length++;
	write(2, error, length);
	exit(1);
}