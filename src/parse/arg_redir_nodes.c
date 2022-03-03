#include "../../inc/minishell.h"

t_built_args	*create_args_node(t_mini *shell, int **ptr_space, int *i)
{
	t_built_args	*new;

	new = malloc(sizeof(t_built_args));
	if (!new)
		return (NULL);
	new = malloc(sizeof(t_built_args));
	new->name = ft_substr(shell->argv, *i, **ptr_space - *i);
	new->next = NULL;
	*i = **ptr_space + 1;
	(*ptr_space)++;
	return (new);
}

void	add_args_to_child(t_command *child, t_built_args *new)
{
	t_built_args	*tmp;

	tmp = child->args;
	if (!tmp)
		child->args = new;
	else
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	add_redir_to_child(t_command *child, t_redir *new)
{
	t_redir	*tmp;

	tmp = child->redirection;
	if (!tmp)
		child->redirection = new;
	else
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_redir	*create_redir_node(t_mini *shell, int **ptr_space, int *i)
{
	t_redir *new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new = malloc(sizeof(t_redir));
	new->type = detect_sep(shell->argv, i);
	*i = **ptr_space + 1;
	(*ptr_space)++;
	new->file_name = ft_substr(shell->argv, *i, **ptr_space - *i);
	*i = **ptr_space + 1;
	(*ptr_space)++;
	new->next = NULL;
	return (new);
}
