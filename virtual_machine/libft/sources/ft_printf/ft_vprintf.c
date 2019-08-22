
#include "ft_printf_local.h"

int 	ft_vprintf(const char *format, va_list *va)
{
	return (ft_vdprintf(1, format, va));
}

int		ft_vdprintf(int fd, const char *format, va_list *va)
{
	int		res;
	t_env	*env;

	env = NULL;
	if (fd < 0)
		return (0);
	res = set_to_plist(&env, format, va);
	if (res != 1)
		return (res);
	res = print_result_fd(env->plist, fd);
	free_printf(env);
	return (res);
}

int		ft_vfprintf(FILE *stream, const char *format, va_list *va)
{
	int		res;
	t_env	*env;

	env = NULL;
	if (stream == NULL)
		return (0);
	res = set_to_plist(&env, format, va);
	if (res != 1)
		return (res);
	res = print_result_file(env->plist, stream);
	free_printf(env);
	return (res);
}

int		ft_vsprintf(char *buf, const char *format, va_list *va)
{
	int		res;
	t_env	*env;

	env = NULL;
	if (buf == NULL)
		return (0);
	res = set_to_plist(&env, format, va);
	if (res != 1)
		return (res);
	res = print_result_str(env->plist, buf);
	free_printf(env);
	return (res);
}

int		ft_vasprintf(char **buf, const char *format, va_list *va)
{
	int		res;
	t_env	*env;

	env = NULL;
	if (buf == NULL)
		return (0);
	res = set_to_plist(&env, format, va);
	if (res != 1)
		return (res);
	*buf = allocate_buffer(env->plist);
	if (*buf == NULL)
	{
		free_printf(env);
		return (-1);
	}
	res = print_result_str(env->plist, *buf);
	free_printf(env);
	return (res);
}