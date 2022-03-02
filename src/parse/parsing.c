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

int	count_cmd(int *sep)
{
	int	i;

	i = 0;
	while (*sep)
	{
		sep++;
		i++;
	}
	return (i + 1);
}

void	alloc_childs(t_mini *shell, int *sep, int *space)
{
	int	*ptr_sep;
	int *ptr_space;
	t_command	*child;
	t_redir		*tmp;
	t_built_args *temp;
	int	i;

	ptr_sep = sep;
	ptr_space = space;
	i = 0;
	child = shell->child;
	while (1)
	{
		child->cmd = ft_substr(shell->argv, i, *ptr_space - i);
		i = *ptr_space + 1;
		ptr_space++;
		while (i != *ptr_sep && i != 1)
		{
			if (shell->argv[i] == '<' || shell->argv[i] == '>')
			{
				tmp = create_redir_node(shell, &ptr_space, &i);
				add_redir_to_child(child, tmp);
			}
			else
			{
				temp = create_args_node(shell, &ptr_space, &i);
				add_args_to_child(child, temp);
			}
		}
		if (*ptr_sep == 0)
			break ;
		ptr_sep++;
		child = child->next;
		i = *ptr_space + 1;
		ptr_space++;
	}
}

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

char	*realloc_string(char *str, char *s2)
{
	free(str);
	str = NULL;
	str = ft_strdup(s2);
	free(s2);
	s2 = NULL;
	return (str);
}

void	dollar_out_quote(t_mini *shell, t_env **env_list)
{
	int	i;
	t_command	*tmp;
	int	dollar_index;
	char *ret;

	tmp = shell->child;
	while (tmp)
	{
		i = 0;
		dollar_index = 0;
		dollar_index = have_a_dollar_out_q(tmp->cmd);
		if (dollar_index != -1)
		{
			ret = replace_dollars(tmp->cmd, env_list, dollar_index, 1);
			tmp->cmd = realloc_string(tmp->cmd, ret);
		}
		while (tmp->args)
		{
			dollar_index = have_a_dollar_out_q(tmp->args->name);
			if (dollar_index != -1)
			{
				ret = replace_dollars(tmp->args->name, env_list, dollar_index, 1);
				tmp->args->name = realloc_string(tmp->args->name, ret);
			}
			else
				tmp->args = tmp->args->next;
		}
		while (tmp->redirection)
		{
			dollar_index = have_a_dollar_out_q(tmp->redirection->file_name);
			if (dollar_index != -1)
			{
				ret = replace_dollars(tmp->redirection->file_name, env_list, dollar_index, 1);
				tmp->redirection->file_name = realloc_string(tmp->redirection->file_name, ret);
			}
			else
				tmp->redirection = tmp->redirection->next;
		}
		tmp = tmp->next;
	}
}

void	quote_remover(t_mini *shell, t_env **env_list, int i)
{
	int	j;

	j = 0;
	while (shell->current->args[i][j])
	{
		if (shell->current->args[i][j] == 34)
		{
			if (have_a_dollar(shell->current->args[i], j + 1))
				realloc_args(shell, env_list, j, i);
			delete_quote(shell, i, &j);
		}
		if (shell->current->args[i][j] == 39)
		{
			delete_quote(shell, i, &j);
			j--;
		}
		j++;
	}
}

void	quotes_cleaner(t_mini *shell, t_env **env_list)
{
	t_command	*tmp;
	int	i = 0;

	tmp = shell->child;
	while (tmp)
	{
		if (detect_quote(tmp->cmd))
			quote_remover(shell, env_list, i); //tmp->cmd
		while (tmp->args)
		{
			if (detect_quote(tmp->args->name))
				quote_remover(shell, env_list, i); //tmp->args->name
			tmp->args = tmp->args->next;
		}
		while (tmp->redirection)
		{
			if (detect_quote(tmp->redirection->file_name))
				quote_remover(shell, env_list, i); //tmp->redirection->file_name
			tmp->redirection = tmp->redirection->next;
		}
		tmp = tmp->next;
	}
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
	shell->cmd_count = count_cmd(sep);
	init_child(shell);
	ptr = sep;
	while (*(ptr++))
		create_n_add_empty_child(shell);

	alloc_childs(shell, sep, space);

	shell->current = shell->first;
	//destroy sep and space
	dollar_out_quote(shell, env_list);
	shell->current = shell->first;
	quotes_cleaner(shell, env_list);
	shell->current = shell->first;
	return (1);
}

int	detect_sep(char *str, int *start)
{
	if (str[*start] == '>')
	{
		if (str[*start + 1] == '>')
		{
			*start += 3;
			return (DB_GREAT);
		}
		*start += 2;
		return (GREAT);
	}
	else if (str[*start] == '<')
	{
		*start += 2;
		return (LESS);
	}
	return (-1);
}


/*int	init_first_child(t_mini *shell, t_arg *tmp, t_command *child)
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
}*/

void	parsing(t_mini *shell, t_env **env_list)
{
	// Notre maniere d'appeler echo est mauvaise puisquil faut boucler lappel a echo pour le
	// nb darguments que notre node contient

	if (!ft_strcmp(shell->argv, ""))
		return ;
	if (!split_arg(shell, env_list))
		return ;
	shell->current = shell->first;
	//acorn_of_wisdom(shell);
}
