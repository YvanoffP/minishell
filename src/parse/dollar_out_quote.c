/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_out_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypetruzz <ypetruzz@student.42lausanne.ch>  +#+  +:+       +#+        */
/*   And: tpauvret                                 +#+   +:+      +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 23:13:46 by ypetruzz          #+#    #+#             */
/*   Updated: 2022/03/03 23:13:46 by ypetruzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	init_var(t_mini *shell, t_alloc *var)
{
	var->i = 0;
	var->ret = NULL;
	var->tmp = shell->child->redirection;
	var->temp = shell->child->args;
	var->dollar_index = NULL;
}

static void	dollar_out_quote_replace(t_alloc *var,
		t_env **env_list, t_mini *shell)
{
	var->ret = replace_dollars(var->tmp->file_name,
			env_list, var->dollar_index, shell);
	var->tmp->file_name = realloc_string(var->tmp->file_name,
			var->ret);
}

static void	dollar_out_quote_ext(t_alloc *var, t_env **env_list, t_mini *shell)
{
	if (var->dollar_index[0] != -1)
	{
		var->ret = replace_dollars(var->child->cmd,
				env_list, var->dollar_index, shell);
		var->child->cmd = realloc_string(var->child->cmd, var->ret);
	}
	while (var->temp)
	{
		if (var->dollar_index)
			free(var->dollar_index);
		var->dollar_index = have_a_dollar_out_q(var->temp->name,
				0);
		if (var->dollar_index[0] != -1)
		{
			var->ret = replace_dollars(var->temp->name,
					env_list, var->dollar_index, shell);
			var->temp->name = realloc_string(var->temp->name, var->ret);
		}
		else
			var->temp = var->temp->next;
	}
}

void	dollar_out_quote(t_mini *shell, t_env **env_list)
{
	t_alloc		var;

	init_var(shell, &var);
	var.child = shell->child;
	while (var.child)
	{
		var.ret = NULL;
		var.i = 0;
		var.temp = var.child->args;
		if (var.dollar_index)
			free(var.dollar_index);
		var.dollar_index = have_a_dollar_out_q(var.child->cmd, 0);
		dollar_out_quote_ext(&var, env_list, shell);
		while (var.tmp)
		{
			if (var.dollar_index)
				free(var.dollar_index);
			var.dollar_index = have_a_dollar_out_q(var.tmp->file_name, 0);
			if (var.dollar_index[0] != -1)
				dollar_out_quote_replace(&var, env_list, shell);
			else
				var.tmp = var.tmp->next;
		}
		var.child = var.child->next;
	}
}
