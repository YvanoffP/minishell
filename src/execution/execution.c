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

static void	execve_call(t_command *child, t_env **env_list)
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

int	execution(t_env **env_list, t_mini *shell)
{
	t_process	*proc;

	proc = malloc(sizeof(t_process));
	proc->ret = 0;
	proc->my_fd[0] = 0;
	proc->my_fd[1] = 0;
	shell->exec = proc;
	backup(1);
	process_heredocs(shell, proc);
	if (shell->child->redirection)
	{
		if (redirection(shell->child->redirection, proc))
			return (backup(0));
	}
	if (shell->child->cmd == NULL && shell->child->redirection == NULL)
	{
		free(proc);
		return (print_error("\0", "command not found", 127));
	}
	if (shell->cmd_count > 1)
		proc->ret = pipe_my_ride(shell, proc, env_list);
	else if (shell->child->cmd != NULL)
		proc->ret = is_builtins(env_list, shell->child);
	backup(0);
	return (proc->ret);
}
