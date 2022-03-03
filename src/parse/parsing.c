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

char	*delete_quote(char *str, int *j)
{
	int		index;
	int		k;
	char	*ret;

	index = 0;
	k = 0;
	ret = malloc(sizeof(char) * (ft_strlen(str) - 2));
	if (!ret)
		return (NULL);
	while (str[k])
	{
		if (k == *j)
			k++;
		if (str[k] == str[*j] && k > *j)
		{
			*j = k++ - 2;
			break ;
		}
		ret[index++] = str[k++];
	}
	while (str[k])
		ret[index++] = str[k++];
	ret[index] = 0;
	free(str);
	return (ret);
}

char	*quote_remover(char *str, t_env **env_list)
{
	char	*ret;
	int		j;

	j = 0;
	while (str[j])
	{
		if (str[j] == 34)
		{
			if (have_a_dollar(str, j + 1))
			{
				ret = replace_dollars(str, env_list, j + 1, 1);
				str = realloc_string(str, ret);
			}
			str = delete_quote(str, &j);
			if (str == NULL)
				return (str);
		}
		if (str[j] == 39)
		{
			str = delete_quote(str, &j);
			j--;
		}
		j++;
	}
	return (str);
}

void	quotes_cleaner(t_mini *shell, t_env **env_list)
{
	t_command		*child;
	t_built_args	*tmp;
	t_redir			*temp;

	child = shell->child;
	while (child)
	{
		tmp = child->args;
		temp = child->redirection;
		if (detect_quote(child->cmd))
			child->cmd = quote_remover(child->cmd, env_list);
		while (tmp)
		{
			if (detect_quote(tmp->name))
				tmp->name = quote_remover(tmp->name, env_list);
			tmp = tmp->next;
		}
		while (temp)
		{
			if (detect_quote(temp->file_name))
				temp->file_name = quote_remover(temp->file_name, env_list);
			temp = temp->next;
		}
		child = child->next;
	}
}

void	destroy_sep_n_space(int **sep, int **space)
{
	free(*sep);
	free(*space);
}

int	split_arg(t_mini *shell, t_env **env_list)
{
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
	destroy_sep_n_space(&sep, &space);
	dollar_out_quote(shell, env_list);
	quotes_cleaner(shell, env_list);
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

int	parsing(t_mini *shell, t_env **env_list)
{
	if (!split_arg(shell, env_list))
		return (0);
	return (1);
}
