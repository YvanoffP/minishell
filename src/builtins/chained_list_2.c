#include "../../inc/minishell.h"

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
