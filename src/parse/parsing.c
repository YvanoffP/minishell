#include "../../inc/minishell.h"

void	parsing(t_mini *shell, t_env **env_list)
{
	if (!ft_strcmp(shell->argv, ""))
		return ;
	split_arg(shell);
	if (!ft_strcmp(shell->arg_split[0], CD))
		cd(shell->arg_split[1]);
	else if (!ft_strcmp(shell->arg_split[0], ECHO_CMD))
		echo_func(shell->arg_split[1], shell->arg_split[2]);
	else if (!ft_strcmp(shell->argv, ENV))
		env_func(env_list);
	else if (!ft_strcmp(shell->arg_split[0], EXPORT))
		export_func(env_list, shell->arg_split[1]);
	else if (!ft_strcmp(shell->arg_split[0], EXIT))
		exit(0);
	else if (!ft_strcmp(shell->arg_split[0], PWD))
		pwd();
	else if (!ft_strcmp(shell->arg_split[0], UNSET))
		unset(shell->arg_split[1], env_list);
}
