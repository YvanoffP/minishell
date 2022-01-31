#include "minishell.h"

t_env	*create_node(char *var_array)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (new_node)
	{
		new_node->var = ft_strdup(var_array);
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
	t_env	*tmp;
	t_env	*new;
	t_env	*copy;

	tmp = *env_list;
	copy = NULL;
	if (*env_list == NULL)
		return (NULL);
	while (tmp != NULL)
	{
		new = create_node(tmp->var);
		if (copy == NULL)
			copy = new;
		else
			add_to_list(&copy, new);
		tmp = tmp->next;
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
	char	*str;

	if (ft_strcmp(tmp->var, tmp->next->var) > 0)
	{
		str = ft_strdup(tmp->next->var);
		free(tmp->next->var);
		tmp->next->var = ft_strdup(tmp->var);
		free(tmp->var);
		tmp->var = ft_strdup(str);
		//TODO : free(str) ??
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
		node = tmp->next;
		free(tmp);
		tmp = node;
	}
}

t_env	*search_in_env(char	*var, t_env **env_list)
{
	t_env	*tmp;

	tmp = *env_list;
	if (tmp == NULL || var == NULL)
		return (NULL);
	while (tmp != NULL && ft_strncmp(tmp->var, var, ft_strlen()) != 0)
		tmp = tmp->next;
	return (tmp);
}

void	replace_var(t_env **env_list, char *var)
{
	t_env	*tmp;

	tmp = search_in_env(var, )
}
