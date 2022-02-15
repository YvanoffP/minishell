#include "minishell.h"

/*void	echo_func(char *str, char *str2)
{
	int	i;

	i = 0;
	if (!str && !str2)
		return ;
	if (str2 == NULL) // MEANS NO FLAG
	{
		while (str[i] != '\0')
			write(1, &str[i++], 1);
		write(1, "\n", 1);
		return ;
	}
	else if (!ft_strcmp(str, "-n"))
	{
		while (str2[i] != '\0')
			write(1, &str2[i++], 1);
		return ;
	}
	write(1, "\n", 1);
}*/

void	echo_func(t_mini *shell)
{
	int	i;

	i = 0;
	if (!ft_strcmp(shell->current->args[1], "-n"))
	{
		i++;
		while (shell->current->args[++i])
		{
			write(1, shell->current->args[i], ft_strlen(shell->current->args[i]));
			if (shell->current->args[i + 1] != NULL)
				write(1, " ", 1);
		}
		return ;
	}
	else
	{
		while (shell->current->args[++i])
		{
			write(1, shell->current->args[i], ft_strlen(shell->current->args[i]));
			if (shell->current->args[i + 1] != NULL)
				write(1, " ", 1);
		}
		write(1, "\n", 1);
	}
}
