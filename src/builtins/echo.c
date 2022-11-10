/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypetruzz <ypetruzz@student.42lausanne.ch>  +#+  +:+       +#+        */
/*   And: tpauvret                                 +#+   +:+      +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 23:13:46 by ypetruzz          #+#    #+#             */
/*   Updated: 2022/03/03 23:13:46 by ypetruzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	acorn_of_wisdom(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	if (str[i] == '-')
	{
		i++;
		while (str[i] == 'n' && str[i])
			i++;
		if (str[i] == '\0')
			return (0);
	}
	return (1);
}

static void	echo_func_ext(t_built_args *args)
{
	while (!acorn_of_wisdom(args->name))
		args = args->next;
	while (args)
	{
		write(1, args->name, ft_strlen(args->name));
		if (args->next)
			write(1, " ", 1);
		args = args->next;
	}
}

void	echo_func(t_built_args *args)
{
	if (!args)
	{
		write(1, "\n", 1);
		return ;
	}
	if (!acorn_of_wisdom(args->name))
	{
		if (!args->next)
			return ;
		args = args->next;
		echo_func_ext(args);
		return ;
	}
	else
	{
		echo_func_ext(args);
		write(1, "\n", 1);
	}
}
