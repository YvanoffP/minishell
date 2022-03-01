#include "minishell.h"

int	is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	check_only_num(char *str)
{
	while (*str && is_num(*str))
		str++;
	if (!*str)
		return (0);
	return (1);
}

int	check_args(char *name)
{
	if (!check_wrong_char(name))
		return (0);
	if (!check_only_num(name))
		return (0);
	return (1);
}

int	export_func(t_env **env_list, t_built_args *args)
{
	int	i;

	i = 1;
	if (args != NULL)
	{
		while (args != NULL)
		{
			if (!check_args(args->name))
				return (str_error("Export arguments wrong : expected identifier", 0));
			if (!add_var_to_list(env_list, args->name))
				return (str_error("Error malloc in the malloc of func add_var_to_list", 0));
			args = args->next;
		}
	}
	else
		print_export_list(env_list);
	return (1);
}
