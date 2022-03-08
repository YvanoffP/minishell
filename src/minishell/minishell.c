/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypetruzz <ypetruzz@student.42lausanne.ch>  +#+  +:+       +#+        */
/*   And: tpauvret                                 +#+   +:+      +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 23:13:46 by ypetruzz          #+#    #+#             */
/*   Updated: 2022/03/03 23:13:46 by ypetruzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_mini(t_mini *shell, t_env **env)
{
	char	buff[4096];
	char	*cwd;
	int		i;

	i = -1;
	cwd = getcwd(buff, 4096);
	shell->argv = NULL;
	shell->exec = NULL;
	shell->child = NULL;
	*env = NULL;
	shell->cmd_count = 0;
	shell->stdin_fd = dup(STDIN_FILENO);
	shell->stdout_fd = dup(STDOUT_FILENO);
	shell->fd_history = 0;
	g_status.infork = NO;
	g_status.status = 0;
	shell->status = 0;
	write_inputrc();
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
	if (shell->argv)
		free(shell->argv);
}
