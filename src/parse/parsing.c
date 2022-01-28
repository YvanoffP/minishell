#include "../../inc/minishell.h"

void	parsing(t_mini *shell, t_env **env_list)
{
//	if (!ft_strcmp(shell->argv, CD))
//		cd();
//	else if (ft_strcmp(shell->argv, ECHO_CMD))
//		echo_func();
	if (!ft_strcmp(shell->argv, ENV))
		env_func(env_list);
	else if (!ft_strcmp(shell->argv, EXPORT))
		export_func(env_list, NULL);
	else if (!ft_strcmp(shell->argv, EXIT))
		exit(0);
	else if (!ft_strcmp(shell->argv, PWD))
		pwd();
//	else if (shell->argv, UNSET))
//		unset();
}
