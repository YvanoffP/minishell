#include "../../inc/minishell.h"

static void	init_var(t_mini *shell, t_alloc *var)
{
	var->i = 0;
	var->ret = NULL;
	var->tmp = shell->child->redirection;
	var->temp = shell->child->args;
	var->dollar_index = 0;
}

static void	dollar_out_quote_replace(t_alloc *var, t_env **env_list)
{
	var->ret = replace_dollars(var->tmp->file_name,
			env_list, var->dollar_index, 1);
	var->tmp->file_name = realloc_string(var->tmp->file_name,
			var->ret);
}

void	dollar_out_quote_ext(t_alloc *var, t_env **env_list)
{
	if (var->dollar_index != -1)
	{
		var->ret = replace_dollars(var->child->cmd,
				env_list, var->dollar_index, 1);
		var->child->cmd = realloc_string(var->child->cmd, var->ret);
	}
	while (var->temp)
	{
		var->dollar_index = have_a_dollar_out_q(var->temp->name);
		if (var->dollar_index != -1)
		{
			var->ret = replace_dollars(var->temp->name,
					env_list, var->dollar_index, 1);
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
		var.temp = var.child->args;
		var.tmp = var.child->redirection;
		var.i = 0;
		var.dollar_index = 0;
		var.dollar_index = have_a_dollar_out_q(var.child->cmd);
		dollar_out_quote_ext(&var, env_list);
		while (var.tmp)
		{
			var.dollar_index = have_a_dollar_out_q(var.tmp->file_name);
			if (var.dollar_index != -1)
				dollar_out_quote_replace(&var, env_list);
			else
				var.tmp = var.tmp->next;
		}
		var.child = var.child->next;
	}
}
