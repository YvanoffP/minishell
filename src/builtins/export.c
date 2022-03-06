/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypetruzz <ypetruzz@student.42lausanne.ch>  +#+  +:+       +#+        */
/*   And: tpauvret                                 +#+   +:+      +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 23:13:46 by ypetruzz          #+#    #+#             */
/*   Updated: 2022/03/03 23:13:46 by ypetruzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	check_only_num(char *str)
{
	while (*str && is_num(*str))
		str++;
	if (!*str)
		return (0);
	return (1);
}

int	check_plus(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i])
	{
		if (str[i] == '+' && str[i + 1] != '=')
			return (0);
		i++;
	}
	return (1);
}

int	check_args(char *name)
{
	if (!check_wrong_char(name))
		return (0);
	if (!check_only_num(name))
		return (0);
	if (!check_plus(name))
		return (0);
	return (1);
}

int	export_func(t_env **env_list, t_built_args *args)
{
	int	i;

	i = 1;
	if (args != NULL)
	{
		while (args != NULL)
		{
			if (!check_args(args->name))
				return (str_error("Export arguments: expected identifier", 0));
			if (!add_var_to_list(env_list, args->name))
				return (str_error("Error malloc", 0));
			args = args->next;
		}
	}
	else
		print_export_list(env_list);
	return (1);
}
