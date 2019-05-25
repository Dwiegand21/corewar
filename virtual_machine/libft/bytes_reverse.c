
#include <stdlib.h>

void		bytes_reverse(void *param, size_t size)
{
	size_t 	i;
	char 	tmp;

	i = 0;
	while (i < size / 2)
	{
		tmp = *(((char *)param) + i);
		*(((char *)param) + i) = *(((char *)param) + size - 1 - i);
		*(((char *)param) + size - 1 - i) = tmp;
		i++;
	}
}