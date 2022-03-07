/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <tpauvret@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:55:40 by tpauvret          #+#    #+#             */
/*   Updated: 2022/03/07 22:55:57 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_pipes(t_command *tmp)
{
	t_command	*cmds;

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
