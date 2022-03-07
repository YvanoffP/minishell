/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypetruzz <ypetruzz@student.42lausanne.ch>  +#+  +:+       +#+        */
/*   And: tpauvret                                 +#+   +:+      +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 23:13:46 by ypetruzz          #+#    #+#             */
/*   Updated: 2022/03/03 23:13:46 by ypetruzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	check_tild(t_mini *shell)
{
	t_command		*tmp;
	t_built_args	*temp;
	char			*ret;

	tmp = shell->child;
	temp = shell->child->args;
	while (tmp)
	{
		while (temp)
		{
			if (temp->name[0] == '~'
				&& temp->name[1] == '\0')
			{
				ret = getenv("HOME");
				free(temp->name);
				temp->name = ft_strdup(ret);
			}
			temp = temp->next;
		}
		tmp = tmp->next;
	}
}

void	need_spaces(t_mini *shell, t_env **env_list)
{
	check_tild(shell);
	dollar_out_quote(shell, env_list);
	quotes_cleaner(shell);
}

void	skip_w_space(char *str, int *i)
{
	while (is_w_space(str[*i]))
		*i += 1;
}

int	have_a_dollar(char *str, int i)
{
	while (str[i] != 34 && str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

void	skip_quote(char *str, int *i)
{
	if (str[*i] == 34 || str[*i] == 39)
	{
		if (str[*i] == 34)
		{
			*i += 1;
			while (str[*i] != 34 && str[*i])
				*i += 1;
			if (!str[*i])
				return ;
		}
		else if (str[*i] == 39)
		{
			*i += 1;
			while (str[*i] != 39 && str[*i])
				*i += 1;
			if (!str[*i])
				return ;
		}
	}
}
