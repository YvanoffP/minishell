/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypetruzz <ypetruzz@student.42lausanne.ch>  +#+  +:+       +#+        */
/*   And: tpauvret                                 +#+   +:+      +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 23:13:46 by ypetruzz          #+#    #+#             */
/*   Updated: 2022/03/03 23:13:46 by ypetruzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

char	*join_path_to_arg(char *path, char *arg)
{
	char	*tmp_path;
	char	*full_path;

	tmp_path = ft_strjoin(path, "/");
	full_path = ft_strjoin(tmp_path, arg);
	free(tmp_path);
	return (full_path);
}

void	execve_call(t_command *child, t_env **env_list)
{
	char	*error;

	if (execve(child->cmd, args_to_array(child), lst_to_array(env_list)) == -1)
	{
		error = ft_strjoin(": ", strerror(errno));
		print_error(child->cmd, error, errno);
		free(error);
		exit(errno);
	}
}

int	exec_program(t_command *child, t_env **env_list)
{
	int	pid;
	int	status;
	int	ret_status;

	pid = fork();
	run_signals(2);
	ret_status = 0;
	if (!pid)
		execve_call(child, env_list);
	else if (pid == -1)
		return (print_error("fork: ", "Fork failed", errno));
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			ret_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			ret_status = 128 + WTERMSIG(status);
			if (WTERMSIG(status) == SIGQUIT)
				write(1, "Quit : 3\n", 9);
		}
		return (ret_status);
	}
	return (77);
}

int	is_builtins(t_env **env_list, t_command *child)
{
	if (!(ft_strcmp(child->cmd, EXPORT))
		|| !(ft_strcmp(child->cmd, "EXPORT")))
		export_func(env_list, child->args);
	else if (!(ft_strcmp(child->cmd, ECHO_CMD))
		|| !(ft_strcmp(child->cmd, "ECHO")))
		echo_func(child->args);
	else if (!(ft_strcmp(child->cmd, UNSET))
		|| !(ft_strcmp(child->cmd, "UNSET")))
		unset(child->args, env_list);
	else if (!(ft_strcmp(child->cmd, CD))
		|| !(ft_strcmp(child->cmd, "CD")))
		cd(child->args);
	else if (!(ft_strcmp(child->cmd, ENV))
		|| !(ft_strcmp(child->cmd, "ENV")))
		env_func(env_list);
	else if (!(ft_strcmp(child->cmd, PWD))
		|| !(ft_strcmp(child->cmd, "PWD")))
		pwd();
	else if (!(ft_strcmp(child->cmd, EXIT))
		|| !(ft_strcmp(child->cmd, "EXIT")))
		exit_func(child->args);
	else
		return (check_path(env_list, child));
	return (0);
}

int	process_cmd(t_env **env_list, t_mini *shell)
{
	t_command	*start;
	t_command	*child;
	bool		error;

	start = shell->child;
	child = shell->child;
	init_pipes(start);
	process_heredocs(shell);
	while (child)
	{
		error = !op_control(child);
		if (!error)
		{
			is_builtins(env_list, child);
			if (!child->next)
				break ;
			fd_reset(shell);
		}
		if (error)
			break ;
		child = child->next;
	}
	close_pipes(start);
	fd_reset(shell);
	return (0);
}
