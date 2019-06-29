
#include <ft_string.h>

int 	ft_strnequ_rev(const char *s1, const char *s2, size_t n)
{
	int		i;
	int 	j;

	i = 0;
	while (s1[i])
		i++;
	j = 0;
	while (s2[j])
		j++;
	while (n)
	{
		if (s1[--i] != s2[--j])
			return (0);
		n--;
	}
	return (1);
}
