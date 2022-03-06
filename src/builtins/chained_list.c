/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chained_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypetruzz <ypetruzz@student.42lausanne.ch>  +#+  +:+       +#+        */
/*   And: tpauvret                                 +#+   +:+      +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 23:13:46 by ypetruzz          #+#    #+#             */
/*   Updated: 2022/03/03 23:13:46 by ypetruzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int		len;
	char	*t;

	len = ft_strlen(var) - 1;
	tmp = *env_list;
	if (tmp == NULL || var == NULL)
		return (0);
	if (var[len] == '+')
		t = ft_substr(var, 0, len);
	else
		t = ft_strdup(var);
	while (tmp != NULL && ft_strcmp(tmp->var, t) != 0)
		tmp = tmp->next;
	if (tmp)
	{
		free(t);
		return (1);
	}
	free(t);
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
	char	*t;
	int		len;

	len = ft_strlen(new_node->var) - 1;
	if (new_node->var[len] == '+')
	{
		t = ft_substr(new_node->var, 0, len);
		free(new_node->var);
		new_node->var = ft_strdup(t);
		free(t);
		tmp = get_in_lst(new_node->var, env_list);
		if (tmp)
		{
			t = ft_strjoin(tmp->value, new_node->value);
			free_node(new_node, tmp, t);
			free(t);
		}
		return ;
	}
	tmp = get_in_lst(new_node->var, env_list);
	if (tmp)
		free_node(new_node, tmp, new_node->value);
}
