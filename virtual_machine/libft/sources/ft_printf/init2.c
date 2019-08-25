
#include "ft_printf_local.h"

t_env	*init_env(void)
{
	t_env	*env;

	env = NULL;
	if (!(env = malloc(sizeof(t_env))))
		env = NULL;
	env->args = NULL;
	env->plist = NULL;
	env->cur = NULL;
	env->max_arg_count = 0;
	env->max_arg_pos = 0;
	env->dollar = -1;
	env->error = 0;
	return (env);
}

int		ft_printf_init(const char *format, t_env *env)
{
	int		args_count;

	args_count = get_args_count(env, (char *)format);
	if (args_count < 0)
		return (0);
	if (!args_init(env, args_count + 1, (char *)format))
		return (0);
	if (!(env->plist = create_plist_node()))
	{
		free_printf(env);
		return (0);
	}
	format_analysis(env, (char *)format);
	return (1);
}

char 	*allocate_buffer(const t_plist *cur)
{
	char 	*buff;
	int		length;

	buff = NULL;
	length = 0;
	while (cur)
	{
		if (cur->original)
			length += cur->original_width;
		else
			length += cur->len;
		cur = cur->next;
	}
	buff = (char *)malloc(sizeof(char) * (length + 1));
	return (buff);
}

int 	set_to_plist(t_env **env, const char *format, va_list *va)
{
	if (!format)
		return (0);
	if (!(*env = init_env()))
		return (0);
	if (!ft_printf_init(format, *env))
		return (-1);
	if (!init_arg_list(*env, va))
		return (-1);
	if (!prepare_plist(*env))
	{
		free_printf(*env);
		return (-1);
	}
	return (1);
}