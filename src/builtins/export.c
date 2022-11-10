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

static int	print_error_export(char *str, char *args, char *msg, int ret)
{
	ft_putstr_fd("minishell: ", 2);
	if (str != NULL)
		ft_putstr_fd(str, 2);
	ft_putstr_fd(args, 2);
	ft_putendl_fd(msg, 2);
	return (ret);
}

int	export_func(t_env **env_list, t_built_args *args)
{
	if (args != NULL)
	{
		while (args != NULL)
		{
			if (!check_args(args->name))
				return (print_error_export("export: ",
						args->name, ": not a valid identifier", 1));
			if (!add_var_to_list(env_list, args->name))
				return (str_error("Error malloc", 0));
			args = args->next;
		}
	}
	else
		print_export_list(env_list);
	return (1);
}
