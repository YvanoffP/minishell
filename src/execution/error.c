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
