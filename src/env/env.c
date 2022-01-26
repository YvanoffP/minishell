#include "../../inc/minishell.h"

void	env_func(char **envp)
{
	while (*envp)
	{
		write(1, *envp, ft_strlen(*envp));
		write(1, "\n", 1);
		envp++;
	}
}
