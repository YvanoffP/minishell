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

t_built_args	*create_args_node(t_mini *shell, int i)
{
	t_built_args	*new;

	new = malloc(sizeof(t_built_args));
	if (!new)
		return (NULL);
	new->name = ft_strdup(shell->current->args[i]);
	new->next = NULL;
	return (new);
}

void	add_to_child(t_command *child, t_built_args *new)
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

int	init_first_child(t_mini *shell, t_arg *tmp, t_command *child)
{
	t_built_args	*temp;
	int				i;

	(void)tmp;
	i = 1;
	child->redirection = NULL;
	child->args = NULL;
	child->next = NULL;
	while (1)
	{
		child->cmd = ft_strdup(shell->current->args[0]);
		if (shell->current->args[i])
		{
			child->args = create_args_node(shell, i);
			while (shell->current->args[++i])
			{
				temp = create_args_node(shell, i);
				add_to_child(child, temp);
			}
		}
		shell->current = shell->current->next;
		break ;
	}
	return (0);
}

t_redir	*create_redir_node(t_mini *shell, t_arg *save)
{
	t_redir *new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->file_name = ft_strdup(shell->current->args[0]);
	new->type = detect_sep(save);
	new->next = NULL;
	return (new);
}

int	fill_child(t_mini *shell, t_command *child, t_arg *save)
{
	int				i;
	t_built_args	*temp;
	t_redir			*tmp;

	i = 0;
	shell->current = shell->current->next;
	tmp = create_redir_node(shell, save);
	add_redir_to_child(child, tmp);
	while (shell->current->args[++i])
	{
		temp = create_args_node(shell, i);
		add_to_child(child, temp);
	}
	return (0);
}

void add_new_child(t_command *child)
{
	t_command *tmp;

	tmp = malloc(sizeof(t_command));
	if (!tmp)
		return ;
	tmp->cmd = NULL;
	child->next = tmp;
}

int	acorn_of_wisdom(t_mini *shell)
{
	t_command	*child;
	t_arg		*tmp;
	t_arg		*save;

	tmp = shell->current;
	child = malloc(sizeof(t_command)); //FREE IT
	child->cmd = NULL;
	shell->child = child;
	if (!tmp->next)
		return (init_first_child(shell, tmp, child));
	tmp = tmp->next;
	save = tmp;
	while (is_sep(tmp->args[0][0]))
	{
		if (tmp->args[0][0] == '|')
		{
			if (!child->cmd)
				init_first_child(shell, tmp, child);
			shell->current = tmp;
			shell->current = shell->current->next;
			save = tmp;
			add_new_child(child);
			child = child->next;
			tmp = tmp->next->next;
			if (!tmp)
			{
				init_first_child(shell, tmp, child);
				break ;
			}
		}
		else
		{
			if (!child->cmd)
				init_first_child(shell, tmp, child);
			save = tmp;
			tmp = tmp->next->next;
			fill_child(shell, child, save);
			while (tmp && (tmp->args[0][0] == '<' || tmp->args[0][0] == '>'))
			{
				shell->current = tmp;
				save = tmp;
				tmp = tmp->next->next;
				fill_child(shell, child, save);
			}
			if (!tmp)
				break ;
		}
	}
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
	acorn_of_wisdom(shell);
}
