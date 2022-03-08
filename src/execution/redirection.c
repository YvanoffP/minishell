/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypetruzz <ypetruzz@student.42lausanne.ch>  +#+  +:+       +#+        */
/*   And: tpauvret                                 +#+   +:+      +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 23:13:46 by ypetruzz          #+#    #+#             */
/*   Updated: 2022/03/03 23:13:46 by ypetruzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	redir_output(t_redir *redir, t_errs *err)
{
	int		open_fd;
	char	*tmp;

	open_fd = open(redir->file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (open_fd == -1)
	{
		err->str_err = ft_strjoin("minishell :", redir->file_name);
		tmp = ft_strdup(err->str_err);
		free(err->str_err);
		err->str_err = ft_strjoin(tmp, " : No such file or directory\n");
		free(tmp);
		return (false);
	}
	dup2(open_fd, STDOUT_FILENO);
	close(open_fd);
	return (true);
}

bool	redir_append(t_redir *redir, t_errs *err)
{
	int		open_fd;
	char	*tmp;

	open_fd = open(redir->file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (open_fd == -1)
	{
		err->str_err = ft_strjoin("minishell :", redir->file_name);
		tmp = ft_strdup(err->str_err);
		free(err->str_err);
		err->str_err = ft_strjoin(tmp, " : No such file or directory\n");
		free(tmp);
		return (false);
	}
	dup2(open_fd, STDOUT_FILENO);
	close(open_fd);
	return (true);
}

bool	redir_input(t_redir *redir, t_errs *err)
{
	int		open_fd;
	char	*tmp;

	open_fd = open(redir->file_name, O_RDONLY);
	if (open_fd == -1)
	{
		err->str_err = ft_strjoin("minishell :", redir->file_name);
		tmp = ft_strdup(err->str_err);
		free(err->str_err);
		err->str_err = ft_strjoin(tmp, " : No such file or directory\n");
		free(tmp);
		return (false);
	}
	dup2(open_fd, STDIN_FILENO);
	close(open_fd);
	return (true);
}

bool	redirect(t_redir *redir, int *pipe_fd, t_errs *err)
{
	t_redir	*redirs;

	redirs = redir;
	if (redirs->type == GREAT)
		return (redir_output(redirs, err));
	else if (redirs->type == DB_GREAT)
		return (redir_append(redirs, err));
	else if (redirs->type == LESS)
		return (redir_input(redirs, err));
	else if (redirs->type == DB_LESS)
		dup2(pipe_fd[0], STDIN_FILENO);
	return (true);
}

bool	exec_redirections(t_redir *redir, int *pipe_fd, t_errs *err)
{
	t_redir	*redirs;

	redirs = redir;
	while (redirs)
	{
		if (!redirect(redirs, pipe_fd, err))
			return (false);
		redirs = redirs->next;
	}
	return (true);
}
