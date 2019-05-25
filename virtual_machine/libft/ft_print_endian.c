
#include <unistd.h>
#include <stdint.h>

void	ft_print_endian()
{
	uint16_t x = 1; /* 0x0001 */
	if (*((uint8_t *) &x) == 0)
		write(1, "big-endian\n", 11);
	else
		write(1, "little-endian\n", 14);
}

