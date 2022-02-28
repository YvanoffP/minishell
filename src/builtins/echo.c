#include "minishell.h"

void	echo_func(t_built_args *args)
{
	int	i;

	i = 0;
	if (!args)
	{
		write(1, "\n", 1);
		return ;
	}
	if (!ft_strcmp(args->name, "-n"))
	{
		if (args->next)
			args = args->next;
		while (args)
		{
			write(1, args->name, ft_strlen(args->name));
			if (args->next)
				write(1, " ", 1);
			args = args->next;
		}
		return ;
	}
	else
	{
		while (args)
		{
			write(1, args->name, ft_strlen(args->name));
			if (args->next)
				write(1, " ", 1);
			args = args->next;
		}
		write(1, "\n", 1);
	}
}
