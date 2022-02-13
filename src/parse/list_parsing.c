#include "../../inc/minishell.h"

void	init_args(t_mini *shell)
{
	t_arg	*args;

	args = malloc(sizeof(t_arg));
	args->args = NULL;
	args->next = NULL;
	shell->first = args;
	shell->current = args;
}

void	add_sep_to_lst(t_mini *shell, int *i)
{
	t_arg	*new;

	new = malloc(sizeof(t_arg));
	if (new)
	{
		new->args = malloc(sizeof(char *) * 2);
		new->args[0] = add_sep_to_node(shell, i);
		new->args[1] = NULL;
		new->next = NULL;
		if (shell->current)
		{
			while (shell->current && shell->current->next)
				shell->current = shell->current->next;
			shell->current->next = new;
			shell->current = new;
		}
		else
			shell->current = new;
	}
}

char	*add_sep_to_node(t_mini *shell, int *i)
{
	int	j;
	char	*ret;

	j = *i;
	//TODO : change this condition with is_sep function
	while (shell->argv[*i] == '|' || shell->argv[*i] == '<' || shell->argv[*i] == '>')
		*i += 1;
	ret = ft_substr(shell->argv, j, (*i - j));
	if (!ret)
		return (NULL);
	return (ret);
}

void	create_n_add_empty_node(t_mini *shell)
{
	t_arg	*new;
	t_arg	*lst;

	new = malloc(sizeof(t_arg));
	lst = shell->first;
	if (new)
	{
		new->args = NULL;
		new->next = NULL;
		while (lst && lst->next)
			lst = lst->next;
		lst->next = new;
	}
}

void	destroy_arg_lst(t_mini *shell)
{
	//Those free functions have to be tested with valgrind because leaks seems not ok
	//With or without the two last free, leaks commands display no leak
	//but if we print shell->first->args after boucle while, shell->first->args contains
	//the last argument

	t_arg	*tmp;

	while (shell->first && shell->first->next)
	{
		tmp = shell->first->next;
		free_array(shell->first->args);
		free(shell->first);
		shell->first = tmp;
	}
	free_array(shell->first->args);
	free(shell->first);
	//USEFUL ? I saw some guys put their pointer on NULL after free. HAD TO CHECK
	//shell->first = NULL;
	//shell->current = NULL;
}
