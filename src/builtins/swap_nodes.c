/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypetruzz <ypetruzz@student.42lausanne.ch>  +#+  +:+       +#+        */
/*   And: tpauvret                                 +#+   +:+      +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 23:13:46 by ypetruzz          #+#    #+#             */
/*   Updated: 2022/03/03 23:13:46 by ypetruzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
		free(name);
		free(value);
	}
}
