#include "../../inc/minishell.h"

int	create_fd_pipe(t_mini *shell, t_process *proc)
{
	int	i;

	i = 0;
	proc->fd = malloc(sizeof(int) * (shell->cmd_count * 2));
	proc->pid = malloc(sizeof(int) * (shell->cmd_count + 1));
	if (!proc->fd || !proc->pid)
		return (print_error("malloc", ": malloc failed", 1));
	while (i < shell->cmd_count)
	{
		if (pipe(proc->fd + i * 2) < 0)
			return (print_error("pipe", ": could not create pipe", 1));
		i++;
	}
	return (0);
}

int	pipe_fork(t_command	*child, t_env **env_list, t_process *proc, int *cmd)
{
	int	i;

	i = 0;
	infork = YES;
	if (child->next)
		if (dup2(proc->fd[*cmd + 1], STDOUT_FILENO) < 0)
			exit(print_error("dup2", "could not Claude (kekw) the fd", 1));
	if (cmd != 0)
		if (dup2(proc->fd[*cmd - 2], STDIN_FILENO) < 0)
			exit(print_error("dup2", "could not Claude (kekw) the fd 1", 1));
	if (child->redirection != NULL)
	{
		if (redirection(child->redirection, proc))
			exit(1);
	}
	while (i < (proc->cmd_count * 2))
		close(proc->fd[i++]);
	proc->ret = is_builtins(env_list, child);
	exit(proc->ret);
}

int	close_fd(t_mini *shell, t_process *proc)
{
	int	i;
	int	status;

	i = 0;
	while (i < (shell->cmd_count * 2))
		close(proc->fd[i++]);
	i = 0;
	while (i < (shell->cmd_count + 1))
	{
		waitpid(proc->pid[i], &status, 0);
		proc->ret = WEXITSTATUS(status);
		i++;
	}
	free(proc->fd);
	free(proc->pid);
	return (proc->ret);
}

int	pipe_my_ride(t_mini *shell, t_process *proc, t_env **env_list)
{
	t_command	*tmp;
	int			cmd;
	int			i;

	i = 0;
	cmd = 0;
	tmp = shell->child;
	shell->cmd_count--;
	proc->cmd_count = shell->cmd_count;
	if (create_fd_pipe(shell, proc))
		return (1);
	while (tmp)
	{
		proc->pid[i] = fork();
		if (proc->pid[i] == -1)
			return (print_error("fork", ": could not fork properly", 1));
		else if (proc->pid[i] == 0)
			pipe_fork(tmp, env_list, proc, &cmd);
		tmp = tmp->next;
		cmd += 2;
		backup(0);
		i++;
	}
	return (close_fd(shell, proc));
}
