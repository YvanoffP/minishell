#include "../../inc/minishell.h"

static void	alloc_struct_init(t_alloc *var, int **ptrsep, int **ptrspace)
{
	var->i = 0;
	var->ptr_space = *ptrspace;
	var->ptr_sep = *ptrsep;
}

static void	alloc_childs_ext(t_alloc *var, t_mini *shell)
{
	while (1)
	{
		var->child->cmd = ft_substr(shell->argv, var->i, *var->ptr_space - var->i);
		var->i = *var->ptr_space + 1;
		var->ptr_space++;
		while (var->i != *var->ptr_sep && var->i != 1)
		{
			if (shell->argv[var->i] == '<' || shell->argv[var->i] == '>')
			{
				var->tmp = create_redir_node(shell, &var->ptr_space, &var->i);
				add_redir_to_child(var->child, var->tmp);
			}
			else
			{
				var->temp = create_args_node(shell, &var->ptr_space, &var->i);
				add_args_to_child(var->child, var->temp);
			}
		}
		if (*var->ptr_sep == 0)
			break ;
		var->ptr_sep++;
		var->child = var->child->next;
		var->i = *var->ptr_space + 1;
		var->ptr_space++;
	}
}

void	alloc_childs(t_mini *shell, int *sep, int *space)
{
	t_alloc	var;

	alloc_struct_init(&var, &sep, &space);
	var.child = shell->child;
	if (!*var.ptr_space)
	{
		var.child->cmd = ft_substr(shell->argv, var.i, ft_strlen(shell->argv));
		return ;
	}
	alloc_childs_ext(&var, shell);
}
