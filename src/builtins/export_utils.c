/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypetruzz <ypetruzz@student.42lausanne.ch>  +#+  +:+       +#+        */
/*   And: tpauvret                                 +#+   +:+      +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 23:13:46 by ypetruzz          #+#    #+#             */
/*   Updated: 2022/03/03 23:13:46 by ypetruzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	check_wrong_char(char *str)
{
	if (*str == '=')
		return (0);
	while (*str)
	{
		if (is_sep(*str) || (*str >= 33 && *str <= 42)
			|| (*str >= 44 && *str <= 47)
			|| (*str == '=' && *(str + 1) == '='))
			return (0);
		str++;
	}
	return (1);
}

void	print_export_list(t_env **env_list)
{
	t_env	*tmp;
	t_env	*sort_list;

	sort_list = sort_list_export(env_list);
	tmp = sort_list;
	while (tmp != NULL)
	{
		if (tmp->var != NULL)
		{
			ft_putstr_fd(tmp->var, 1);
			write(1, "=", 1);
			ft_putstr_fd(tmp->value, 1);
		}
		write(1, "\n", 1);
		tmp = tmp->next;
	}
	delete_list(sort_list);
}

int	add_var_to_list(t_env **env_list, char *args)
{
	t_env	*new_node;

	new_node = create_node(args);
	if (!new_node)
		return (0);
	if (!is_in_lst(new_node->var, env_list))
		add_to_list(env_list, new_node);
	else
		replace_in_lst(new_node, env_list);
	return (1);
}

char	**env_duplicate(char **envp)
{
	char	**copy;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	copy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	copy[i] = 0;
	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		i++;
	}
	return (copy);
}
