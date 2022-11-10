/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypetruzz <ypetruzz@student.42lausanne.ch>  +#+  +:+       +#+        */
/*   And: tpauvret                                 +#+   +:+      +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 23:13:46 by ypetruzz          #+#    #+#             */
/*   Updated: 2022/03/03 23:13:46 by ypetruzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_built_args *args, t_env **env_list)
{
	t_env	*check_node;
	t_env	*prev_node;

	check_node = *env_list;
	if (!args || *env_list == NULL)
		return ;
	while (ft_strcmp(args->name, check_node->var) != 0 && args->name)
	{
		prev_node = check_node;
		check_node = check_node->next;
		if (check_node == NULL)
			return ;
	}
	prev_node->next = check_node->next;
	free(check_node->var);
	free(check_node->value);
	free(check_node);
}
