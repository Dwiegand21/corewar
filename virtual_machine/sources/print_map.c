
#include "virtual_machine.h"

void		print_map(uint8_t *map)
{
	unsigned char	l;
	unsigned char	r;

	for (int i = 0; i < 64; i++)
	{
		for (int j = 0; j < 64; j++)
		{
			l = (((map[j + i * 64]) >> 4) & 0x0F);
			r = ((map[j + i * 64]) & 0x0F);
			if (l > 9)
				printf("%c", l % 10 + 'a');
			else
				printf("%c", l + '0');
			if (r > 9)
				printf("%c", r % 10 + 'a');
			else
				printf("%c", r + '0');
			printf(" ");
		}
		printf("\n");
	}
}
