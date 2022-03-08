/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpauvret <tpauvret@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:55:40 by tpauvret          #+#    #+#             */
/*   Updated: 2022/03/08 14:19:46 by tpauvret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_command	*init_pipes(t_mini *shell, t_command **child)
{
	t_command	*tmp;
	t_command	*cmds;

	tmp = shell->child;
	*child = shell->child;
	cmds = tmp;
	while (cmds)
	{
		pipe(cmds->fd);
		cmds = cmds->next;
	}
	return (tmp);
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

bool	ft_lstall(t_redir *lst, bool (*f)(void *, t_errs *), t_errs *err)
{
	while (lst)
	{
		if (!f(lst->file_name, err))
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
