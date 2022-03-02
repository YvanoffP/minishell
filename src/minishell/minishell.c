#include "minishell.h"

void	init_mini(t_mini *shell, t_env **env)
{
	char	buff[4096];
	char	*cwd;
	int		i;

	i = -1;
	cwd = getcwd(buff, 4096);
	shell->mini_cwd = sub_path(cwd);
	shell->argv = NULL;
	shell->cmd_count = 0;
	shell->child = NULL;
	*env = NULL;
	shell->fd_history = 0;
	infork = NO;
}

void	init_env(t_env **env_list, char **env)
{
	t_env	*new_node;
	char	**var_array;
	int		i;

	new_node = NULL;
	var_array = env_duplicate(env);
	i = 0;
	while (var_array[i])
	{
		new_node = create_node(var_array[i]);
		if (!env_list)
			env_list = &new_node;
		else
			add_to_list(env_list, new_node);
		i++;
	}
	free_array(var_array);
}

void	exit_shell(t_mini *shell)
{
	free(shell->mini_cwd);
	if (shell->argv)
		free(shell->argv);
	//Check to free t_arg struct
}
