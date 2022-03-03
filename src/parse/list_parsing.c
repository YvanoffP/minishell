/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypetruzz <ypetruzz@student.42lausanne.ch>  +#+  +:+       +#+        */
/*   And: tpauvret                                 +#+   +:+      +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 23:13:46 by ypetruzz          #+#    #+#             */
/*   Updated: 2022/03/03 23:13:46 by ypetruzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_child(t_mini *shell)
{
	t_command	*child;

	child = malloc(sizeof(t_command));
	child->cmd = NULL;
	child->args = NULL;
	child->redirection = NULL;
	child->next = NULL;
	shell->child = child;
}

void	create_n_add_empty_child(t_mini *shell)
{
	t_command	*new;
	t_command	*lst;

	new = malloc(sizeof(t_command));
	lst = shell->child;
	if (new)
	{
		new->redirection = NULL;
		new->args = NULL;
		new->cmd = NULL;
		new->next = NULL;
		while (lst && lst->next)
			lst = lst->next;
		lst->next = new;
	}
}
