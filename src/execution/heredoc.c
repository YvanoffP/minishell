/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <tpauvret@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:56:26 by tpauvret          #+#    #+#             */
/*   Updated: 2022/03/07 22:57:10 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_db_less(char *stop, int *heredoc_fd)
{
	char	*line;

	signal(SIGINT, stop_heredoc);
	line = readline("\e[1;32m> \e[0m");
	while (line)
	{
		if (ft_strcmp(line, stop) == 0)
		{
			close(heredoc_fd[1]);
			close(heredoc_fd[0]);
			break ;
		}
		ft_putendl_fd(line, heredoc_fd[1]);
		free(line);
		line = readline("\e[1;32m> \e[0m");
	}
	free(line);
	exit(0);
}

int	redir_heredocs(t_redir *redir, int fd, bool last)
{
	int		heredoc_fd[2];
	pid_t	pid;
	int		wstatus;

	signal(SIGINT, SIG_IGN);
	pipe(heredoc_fd);
	pid = fork();
	if (pid == -1)
		return (print_error(NULL, ": fork failed", 1));
	if (pid == 0)
		exec_db_less(redir->file_name, heredoc_fd);
	waitpid(pid, &wstatus, 0);
	signal(SIGINT, newline);
	if (last)
		dup2(heredoc_fd[0], fd);
	close(heredoc_fd[1]);
	close(heredoc_fd[0]);
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 130)
		return (1);
	return (0);
}

int	count_db_less(t_redir *redir)
{
	t_redir	*tmp;
	int		ret;

	tmp = redir;
	ret = 0;
	while (tmp)
	{
		if (tmp->type == DB_LESS)
			ret++;
		tmp = tmp->next;
	}
	return (ret);
}

int	exec_heredocs(t_redir *redir, int stdin_fd)
{
	t_redir	*tmp;
	int		count;

	tmp = redir;
	count = count_db_less(tmp);
	while (tmp)
	{
		if (tmp->type == DB_LESS)
		{
			if (redir_heredocs(tmp, stdin_fd, count-- == 1))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	process_heredocs(t_mini *shell)
{
	t_command	*child;
	t_redir		*redir;

	child = shell->child;
	while (child)
	{
		redir = child->redirection;
		while (redir)
		{
			if (redir->type == DB_LESS)
				exec_heredocs(redir, child->fd[0]);
			redir = redir->next;
		}
		child = child->next;
	}
}
