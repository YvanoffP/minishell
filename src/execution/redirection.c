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

int	great_than(int *fd, t_redir *redirection)
{
	*fd = open(redirection->file_name,
			O_CREAT | O_TRUNC | O_RDONLY | O_WRONLY, 0644);
	if ((*fd) < 0)
		return (1);
	dup2((*fd), STDOUT_FILENO);
	close((*fd));
	return (0);
}

int	less_than(int *fd, t_redir *redirection)
{
	*fd = open(redirection->file_name, O_RDONLY);
	if ((*fd) < 0)
		return (1);
	dup2((*fd), STDIN_FILENO);
	close((*fd));
	return (0);
}

int	db_great_than(int *fd, t_redir *redirection)
{
	*fd = open(redirection->file_name,
			O_CREAT | O_RDONLY | O_WRONLY | O_APPEND, 0644);
	if ((*fd) < 0)
		return (1);
	dup2((*fd), STDOUT_FILENO);
	close((*fd));
	return (0);
}

int	redirection(t_redir *redirection, t_process *proc)
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
