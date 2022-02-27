#include "../../inc/minishell.h"

char *find_env_var(char *str, int *i, t_env **env_list)
{
	char *name;
	int	j;
	t_env	*list;

	*i += 1;
	j = *i;
	list = *env_list;
	while (!is_w_space(str[*i]) && str[*i] && str[*i] != '$' && str[*i] != 34 && str[*i] != 39)
		*i += 1;
	name = ft_substr(str, j, (*i - j));
	while (ft_strcmp(name, list->var) && list->next != NULL)
		list = list->next;
	if (ft_strcmp(name, list->var))
	{
		free(name);
		return (NULL);
	}
	free(name);
	name = ft_strdup(list->value);
	return (name);
}

int	split_arg(t_mini *shell, t_env **env_list)
{
	//TODO : free int*
	int	*sep;
	int	*space;
	int	*ptr;

	if (check_quote_err(shell->argv))
		return (0);
	if (check_args_error(shell->argv))
		return (str_error("Args error detected", 0));
	sep = parse_sep(shell->argv);
	if (sep == NULL)
		return (str_error("Sep error detected", 0));
	shell->argv = pimp_my_string(shell, sep);
	free(sep);
	sep = parse_sep(shell->argv);
	space = parse_space(shell->argv);
	init_args(shell);
	ptr = sep;
	while (*(ptr++))
	{
		create_n_add_empty_node(shell);
		create_n_add_empty_node(shell);
	}
	alloc_args_tab(shell, sep, space);
	shell->current = shell->first;
	//destroy sep and space
	dollar_out_quote(shell, env_list);
	shell->current = shell->first;
	quotes_cleaner(shell, env_list);
	shell->current = shell->first;
	return (1);
}

int	detect_sep(t_arg *tmp)
{
	if (!ft_strcmp(tmp->args[0], ">"))
		return (GREAT);
	else if (!ft_strcmp(tmp->args[0], ">>"))
		return (DB_GREAT);
	else if (!ft_strcmp(tmp->args[0], "<"))
		return (LESS);
	return (-1);
}

int	init_first_child(t_mini *shell, t_arg *tmp, t_command *child)
{
	t_built_args	*temp;
	int				i;

	i = 1;
	child->redirection = malloc(sizeof(t_redir)); //FREE IT
	child->redirection->type = detect_sep(tmp);
	while (shell->current != tmp)
	{
		child->cmd = ft_strdup(shell->current->args[0]);
		if (shell->current->args[i])
		{
			child->args = malloc(sizeof(t_built_args));
			child->args->name = ft_strdup(shell->current->args[i]);
			child->args->next = NULL;
			temp = child->args;
			while (shell->current->args[++i])
			{
				child->args->next = malloc(sizeof(t_built_args));
				child->args = child->args->next;
				child->args->name = ft_strdup(shell->current->args[i]);
				child->args->next = NULL;
			}
			child->args = temp;
		}
		shell->current = shell->current->next;
	}
	return (0);
}

int	fill_child(t_mini *shell, t_command *child)
{
	int				i;
	t_built_args	*temp;

	i = 0;
	temp = child->args;
	shell->current = shell->current->next;
	child->redirection->file_name = ft_strdup(shell->current->args[0]);
	while (shell->current->args[++i])
	{
		if (child->args)
		{
			while (child->args->next)
				child->args = child->args->next;
			child->args->next = malloc(sizeof(t_built_args));
			child->args = child->args->next;
			child->args->name = ft_strdup(shell->current->args[i]);
			child->args->next = NULL;
		}
		else
		{
			child->args = malloc(sizeof(t_built_args));
			child->args->name = ft_strdup(shell->current->args[i]);
			child->args->next = NULL;
		}
	}
	child->args = temp;
	return (0);
}

int	acorn_of_wisdom(t_mini *shell)
{
	t_command	*child;
	t_arg		*tmp;

	tmp = shell->current;
	tmp = tmp->next;
	child = malloc(sizeof(t_command)); //FREE IT
	while (is_sep(tmp->args[0][0]))
	{
		if (tmp->args[0][0] == '|')
		{
			fill_child(shell, child);
			shell->current = tmp;
		}
		else
		{
			init_first_child(shell, tmp, child);
			tmp = tmp->next->next;
			fill_child(shell, child);
			if (!tmp)
				break ;
			while (tmp->args[0][0] == '<' || tmp->args[0][0] == '>')
			{
				shell->current = tmp;
				tmp = tmp->next->next;
				fill_child(shell, child);
			}
		}
	}
	shell->child = child;
	return (0);
}

void	parsing(t_mini *shell, t_env **env_list)
{
	// Notre maniere d'appeler echo est mauvaise puisquil faut boucler lappel a echo pour le
	// nb darguments que notre node contient

	if (!ft_strcmp(shell->argv, ""))
		return ;
	if (!split_arg(shell, env_list))
		return ;
	shell->current = shell->first;
	if (shell->first->next)
		acorn_of_wisdom(shell);
}
