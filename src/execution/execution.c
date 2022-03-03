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
	if (execve(child->cmd, args_to_array(child), lst_to_array(env_list)) == -1)
		print_error(child->cmd, "Execve failed", -1);
	exit(0);
}

int	exec_program(t_command *child, t_env **env_list)
{
	int	pid;
	int	status;
	int	ret_status;

	pid = fork();
	ret_status = 0;
	if (!pid)
		execve_call(child, env_list);
	else if (pid == -1)
		return (print_error("fork: ", "Fork failed", -2));
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			ret_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			ret_status =  128 + WTERMSIG(status);
			if (WTERMSIG(status) == SIGQUIT)
				write(1, "Quit : 3\n", 9);
		}
		return (ret_status);
	}
	return (100);
}

int	is_builtins(t_env **env_list, t_command *child)
{
	if (!ft_strcmp(child->cmd, EXPORT))
		export_func(env_list, child->args);
	else if (!ft_strcmp(child->cmd, ECHO_CMD))
		echo_func(child->args);
	else if (!ft_strcmp(child->cmd, UNSET))
		unset(child->args, env_list);
	else if (!ft_strcmp(child->cmd, CD))
		cd(child->args->name);
	else if (!ft_strcmp(child->cmd, ENV))
		env_func(env_list);
	else if (!ft_strcmp(child->cmd, PWD))
		pwd();
	else if (!ft_strcmp(child->cmd, EXIT))
		exit_func(child->args);
	else
		return (check_path(env_list, child));
	return (0);
}

int	execution(t_env **env_list, t_mini *shell)
{
	t_process *proc;

	proc = malloc(sizeof(t_process));	// BRING IT BABE
	proc->ret = 0;
	proc->my_fd[0] = 0;
	proc->my_fd[1] = 0;
	shell->exec = proc;
	backup(1);
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
