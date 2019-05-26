
#include <stdlib.h>
#include <string.h>

void	*ft_memalloc(size_t size)
{
	char 	*new;

	new = NULL;
	new = malloc(size);
	if (new != NULL)
	{
		while (size)
		{
			size--;
			new[size] = 0;
		}
	}
	return ((void *)new);
}