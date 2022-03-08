/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <tpauvret@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 20:57:11 by tpauvret          #+#    #+#             */
/*   Updated: 2022/03/08 21:05:45 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	great_than(int *fd, t_redir *redirection)
{
	*fd = open(redirection->file_name,
			O_CREAT | O_TRUNC | O_RDONLY | O_WRONLY, 0644);
	if ((*fd) < 0)
		return (file_error(redirection));
	dup2((*fd), STDOUT_FILENO);
	close((*fd));
	return (0);
}

static int	less_than(int *fd, t_redir *redirection)
{
	*fd = open(redirection->file_name, O_RDONLY);
	if ((*fd) < 0)
		return (file_error(redirection));
	dup2((*fd), STDIN_FILENO);
	close((*fd));
	return (0);
}

static int	db_great_than(int *fd, t_redir *redirection)
{
	*fd = open(redirection->file_name,
			O_CREAT | O_RDONLY | O_WRONLY | O_APPEND, 0644);
	if ((*fd) < 0)
		return (file_error(redirection));
	dup2((*fd), STDOUT_FILENO);
	close((*fd));
	return (0);
}

int	ft_redirection(t_redir *redirection, t_process *proc)
{
	while (redirection != NULL)
	{
		if (redirection->type == LESS)
		{
			if (less_than(&proc->my_fd[0], redirection))
				return (1);
		}
		else if (redirection->type == GREAT)
		{
			if (great_than(&proc->my_fd[1], redirection))
				return (1);
		}
		else if (redirection->type == DB_GREAT)
		{
			if (db_great_than(&proc->my_fd[1], redirection))
				return (1);
		}
		redirection = redirection->next;
	}
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
	if (shell->child->redirection)
	{
		if (ft_redirection(shell->child->redirection, proc))
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
