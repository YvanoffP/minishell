#include "minishell.h"

t_env	*create_node(char *var_array)
{
	t_env	*new_node;
	int		i;

	new_node = malloc(sizeof(t_env));
	i = 0;
	if (new_node)
	{
		while (var_array[i] != '=' && var_array[i])
			i++;
		new_node->var = ft_substr(var_array, 0, i);
		if (var_array[i] == '\0')
		{
			new_node->value = ft_strdup("");
			new_node->next = NULL;
			return (new_node);
		}
		i++;
		new_node->value = ft_substr(var_array, i, (ft_strlen(var_array) - i));
		new_node->next = NULL;
		return (new_node);
	}
	return (NULL);
}

t_env	*dup_node(char *name, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (new_node)
	{
		new_node->var = ft_strdup(name);
		new_node->value = ft_strdup(value);
		new_node->next = NULL;
		return (new_node);
	}
	return (NULL);
}

void	add_to_list(t_env **env_list, t_env *new_node)
{
	t_env	*list;

	if (!env_list || !new_node)
		return ;
	if (*env_list)
	{
		list = *env_list;
		while (list && list->next)
			list = list->next;
		list->next = new_node;
	}
	else
		*env_list = new_node;
}

t_env	*duplicate_list(t_env **env_list)
{
	t_env	*list;
	t_env	*new;
	t_env	*copy;

	list = *env_list;
	copy = NULL;
	if (*env_list == NULL)
		return (NULL);
	while (list != NULL)
	{
		new = dup_node(list->var, list->value);
		if (copy == NULL)
			copy = new;
		else
			add_to_list(&copy, new);
		list = list->next;
	}
	return (copy);
}

int	count_list(t_env **list)
{
	int		i;
	t_env	*tmp;

	tmp = *list;
	i = 0;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	swap_nodes(t_env *tmp)
{
	char	*name;
	char	*value;

	if (ft_strcmp(tmp->var, tmp->next->var) > 0)
	{
		name = ft_strdup(tmp->next->var);
		value = ft_strdup(tmp->next->value);
		free(tmp->next->var);
		free(tmp->next->value);
		tmp->next->var = ft_strdup(tmp->var);
		tmp->next->value = ft_strdup(tmp->value);
		free(tmp->var);
		free(tmp->value);
		tmp->var = ft_strdup(name);
		tmp->value = ft_strdup(value);
		//TODO : free(value) + free(name) ??
		//free(name);
		//free(value);
	}
}

t_env	*sort_list_export(t_env **env_list)
{
	t_env	*tmp;
	t_env	*sort_list;
	int		i;

	sort_list = duplicate_list(env_list);
	i = count_list(&sort_list);
	tmp = sort_list;
	while (i > 0)
	{
		tmp = sort_list;
		while (tmp->next != NULL)
		{
			swap_nodes(tmp);
			tmp = tmp->next;
		}
		i--;
	}
	return (sort_list);
}

void	delete_list(t_env *env_list)
{
	t_env	*tmp;
	t_env	*node;

	tmp = env_list;
	if (env_list == NULL)
		return ;
	while (tmp != NULL)
	{
		free(tmp->var);
		free(tmp->value);
		node = tmp->next;
		free(tmp);
		tmp = node;
	}
}

int	is_in_lst(char	*var, t_env **env_list)
{
	t_env	*tmp;

	tmp = *env_list;
	if (tmp == NULL || var == NULL)
		return (0);
	//DOUTE : CHECK SI LE STRCMP SEXEC CORRECTEMENT
	while (tmp != NULL && ft_strcmp(tmp->var, var) != 0)
		tmp = tmp->next;
	if (tmp)
		return (1);
	return (0);
}

t_env	*get_in_lst(char *var, t_env **env_list)
{
	t_env	*tmp;

	tmp = *env_list;
	if (tmp == NULL || var == NULL)
		return (NULL);
	while (tmp != NULL && ft_strcmp(tmp->var, var) != 0)
		tmp = tmp->next;
	if (tmp)
		return (tmp);
	return (NULL);
}

void	replace_in_lst(t_env *new_node, t_env **env_list)
{
	t_env	*tmp;

	tmp = get_in_lst(new_node->var, env_list);
	if (tmp)
	{
		free(tmp->value);
		tmp->value = ft_strdup(new_node->value);
		free(new_node->var);
		free(new_node->value);
		free(new_node);
	}
}
