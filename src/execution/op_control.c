/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_control.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <tpauvret@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:57:28 by tpauvret          #+#    #+#             */
/*   Updated: 2022/03/08 14:14:48 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_stdout_redir(t_redir *redir)
{
	t_redir		*redirs;

	redirs = redir;
	if (redir->type == GREAT || redir->type == DB_GREAT)
		return (true);
	return (false);
}

void	fd_reset(t_mini *shell)
{
	dup2(shell->stdout_fd, STDOUT_FILENO);
	dup2(shell->stdin_fd, STDIN_FILENO);
}

void	close_pipes(t_command *child, t_mini *shell)
{
	t_command	*cmds;

	cmds = child;
	if (shell->err)
		while (shell->err->prev != NULL)
			shell->err = shell->err->prev;
	if (shell->err)
	{
		while (shell->err->next)
		{
			ft_putstr_fd(shell->err->str_err, STDERR_FILENO);
			shell->err = shell->err->next;
		}
	}
	destroy_err(shell);
	while (cmds)
	{
		close(cmds->fd[0]);
		close(cmds->fd[1]);
		cmds = cmds->next;
	}
	fd_reset(shell);
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

bool	op_control(t_command *child, t_errs *err)
{
	t_command	*tmp;
	t_redir		*redirs;

	tmp = child;
	redirs = child->redirection;
	left_pipe(tmp);
	if (!ft_lstall(redirs, input_file_exist))
		return (false);
	if (!exec_redirections(redirs, tmp->fd, err))
		return (false);
	if (!ft_lstany(redirs, is_stdout_redir))
		right_pipe(tmp);
	close(tmp->fd[1]);
	return (true);
}
