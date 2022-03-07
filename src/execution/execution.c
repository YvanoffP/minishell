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

void	init_pipes(t_command *tmp)
{
	t_command *cmds;

	cmds = tmp;
	while (cmds)
	{
		pipe(cmds->fd);
		cmds = cmds->next;
	}
}

void	left_pipe(t_command *cmds)
{
	if (cmds->prev)
	{
		dup2(cmds->prev->fd[0], STDIN_FILENO);
		close(cmds->prev->fd[0]);
	}
}

void	right_pipe(t_command *cmds)
{
	if (cmds->next)
		dup2(cmds->fd[1], STDOUT_FILENO);
}

bool	ft_lstall(t_redir *lst, bool (*f)(void *))
{
	while (lst)
	{
		if (!f(lst->file_name))
			return (false);
		lst = lst->next;
	}
	return (true);
}

bool	input_file_exist(void *redir_ptr)
{
	struct stat	buf;
	t_redir		*redir;

	redir = redir_ptr;
	if (redir->type != LESS)
		return (true);
	if (stat(redir->file_name, &buf) == -1)
	{
		print_error("Permission denied new part", ": relou", 1);
		return (false);
	}
	return (true);
}

bool	redir_output(t_redir *redir)
{
	int	open_fd;

	open_fd = open(redir->file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (open_fd == -1)
	{
		print_error("Permission denied new part", ": AHAH", 1);
		return (false);
	}
	dup2(open_fd, STDOUT_FILENO);
	close(open_fd);
	return (true);
}

bool	redir_append(t_redir *redir)
{
	int	open_fd;

	open_fd = open(redir->file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (open_fd == -1)
	{
		print_error("Permission denied new part", ": AHAH", 1);
		return (false);
	}
	dup2(open_fd, STDOUT_FILENO);
	close(open_fd);
	return (true);
}

bool	redir_input(t_redir *redir)
{
	int	open_fd;

	open_fd = open(redir->file_name, O_RDONLY);
	if (open_fd == -1)
	{
		print_error("Permission denied new part", ": AHAH", 1);
		return (false);
	}
	dup2(open_fd, STDIN_FILENO);
	close(open_fd);
	return (true);
}

bool	redirect(t_redir *redir, int *pipe_fd)
{
	t_redir	*redirs;

	redirs = redir;
	if (redirs->type == GREAT)
		return (redir_output(redirs));
	else if (redirs->type == DB_GREAT)
		return (redir_append(redirs));
	else if (redirs->type == LESS)
		return (redir_input(redirs));
	else if (redirs->type == DB_LESS)
		dup2(pipe_fd[0], STDIN_FILENO);
	return (true);
}

bool	exec_redirections(t_redir *redir, int *pipe_fd)
{
	t_redir	*redirs;

	redirs = redir;
	while (redirs)
	{
		if (!redirect(redirs, pipe_fd))
			return (false);
		redirs = redirs->next;
	}
	return (true);
}

bool	ft_lstany(t_redir *lst, bool (*f)(t_redir *))
{
	while (lst)
	{
		if (f(lst))
			return (true);
		lst = lst->next;
	}
	return (false);
}

bool	is_stdout_redir(t_redir *redir)
{
	t_redir		*redirs;

	redirs = redir;
	if (redir->type == GREAT || redir->type == DB_GREAT)
		return (true);
	return (false);
}

bool	op_control(t_command *child)
{
	t_command	*tmp;
	t_redir		*redirs;

	tmp = child;
	redirs = child->redirection;
	left_pipe(tmp);
	if (!ft_lstall(redirs, input_file_exist))
		return (false);
	if (!exec_redirections(redirs, tmp->fd))
		return (false);
	if (!ft_lstany(redirs, is_stdout_redir))
		right_pipe(tmp);
	close(tmp->fd[1]);
	return (true);
}

void	fd_reset(t_mini *shell)
{
	dup2(shell->stdout_fd, STDOUT_FILENO);
	dup2(shell->stdin_fd, STDIN_FILENO);
}

void	close_pipes(t_command *child)
{
	t_command *cmds;

	cmds = child;
	while (cmds)
	{
		close(cmds->fd[0]);
		close(cmds->fd[1]);
		cmds = cmds->next;
	}
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

int	execution(t_env **env_list, t_mini *shell)
{
	t_process	*proc;

	proc = malloc(sizeof(t_process));
	proc->ret = 0;
	proc->my_fd[0] = 0;
	proc->my_fd[1] = 0;
	shell->exec = proc;
	backup(1);
	process_heredocs(shell);
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
