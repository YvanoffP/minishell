/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypetruzz <ypetruzz@student.42lausanne.ch>  +#+  +:+       +#+        */
/*   And: tpauvret                                 +#+   +:+      +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 23:13:46 by ypetruzz          #+#    #+#             */
/*   Updated: 2022/03/03 23:13:46 by ypetruzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_errs(t_mini *shell)
{
	shell->err = malloc(sizeof(t_errs));
	shell->err->error = false;
	shell->err->str_err = NULL;
	shell->err->next = NULL;
	shell->err->prev = NULL;
}

void	add_new_err_node(t_errs *err)
{
	t_errs	*new;

	new = malloc(sizeof(t_errs));
	new->error = false;
	new->str_err = NULL;
	new->next = NULL;
	new->prev = NULL;
	new->prev = err;
	err->next = new;
}

void	destroy_err(t_mini *shell)
{
	t_errs	*tmp;

	while (shell->err)
	{
		tmp = shell->err->prev;
		if (shell->err->str_err)
			free(shell->err->str_err);
		free(shell->err);
		shell->err = tmp;
	}
}

int	backup(int flag)
{
	static int	stdin;
	static int	stdout;
	static int	stderr;

	if (flag)
	{
		stdin = dup(STDIN_FILENO);
		stdout = dup(STDOUT_FILENO);
		stderr = dup(STDERR_FILENO);
	}
	else if (!flag)
	{
		dup2(stdin, 0);
		dup2(stdout, 1);
		dup2(stderr, 2);
	}
	return (1);
}

void	shell_error(t_mini *shell)
{
	fd_reset(shell);
	add_new_err_node(shell->err);
	shell->err = shell->err->next;
}
