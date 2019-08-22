
#include "ft_printf_local.h"

int			print_result_fd(t_plist *cur, int fd)
{
	int res;

	res = 0;
	while (cur)
	{
		if (cur->original)
		{
			res += cur->original_width;
			write(fd, cur->original, cur->original_width);
		}
		else
		{
			res += cur->len;
			write(fd, cur->prepared, cur->len);
		}
		cur = cur->next;
	}
	return (res);
}

int			print_result_file(t_plist *cur, FILE *file)
{
	int res;

	res = 0;
	while (cur)
	{
		if (cur->original)
		{
			res += cur->original_width;
			fwrite(cur->original, sizeof(char), cur->original_width, file);
//			write(fd, cur->original, cur->original_width);
		}
		else
		{
			res += cur->len;
			fwrite(cur->prepared, sizeof(char), cur->len, file);
//			write(fd, cur->prepared, cur->len);
		}
		cur = cur->next;
	}
	return (res);
}

int 		print_result_str(t_plist *cur, char *buff)
{
	int		length;

	length = 0;
	while (cur)
	{
		if (cur->original)
		{
			ft_memcpy(buff + length, cur->original, cur->original_width);
			length += cur->original_width;
		}
		else
		{
			ft_memcpy(buff + length, cur->prepared, cur->len);
			length += cur->len;
		}
		cur = cur->next;
	}
	buff[length] = 0;
	return (length);
}