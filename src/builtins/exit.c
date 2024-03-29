/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypetruzz <ypetruzz@student.42lausanne.ch>  +#+  +:+       +#+        */
/*   And: tpauvret                                 +#+   +:+      +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 23:13:46 by ypetruzz          #+#    #+#             */
/*   Updated: 2022/03/03 23:13:46 by ypetruzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_digit_ext(char *arg)
{
	char	*error;
	int		exit_status;

	error = ft_strjoin(arg, ": numeric argument required");
	exit_status = print_error("exit: ", error, 255);
	free(error);
	exit(exit_status);
}

void	check_digit(char *arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			check_digit_ext(arg);
		i++;
		if (arg[i] == 32)
		{
			skip_w_space(arg, &i);
			if (arg[i] != '\0')
				check_digit_ext(arg);
		}
	}
}

int	check_exit(char *arg)
{
	int				i;
	char			*error;
	long long		exit_status;

	i = 0;
	skip_w_space(arg, &i);
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	check_digit(arg + i);
	exit_status = ft_atoi(arg + i);
	if (exit_status < 0)
	{
		error = ft_strjoin(arg, ": numeric argument required");
		exit_status = print_error("exit: ", error, 255);
		free(error);
		exit(exit_status);
	}
	if (i == 0)
		return (exit_status);
	return (exit_status * -1);
}

int	exit_func(t_built_args *args)
{
	int	i;

	if (args == NULL)
	{
		if (g_status.infork == NO)
			ft_putendl_fd("exit", 1);
		exit(0);
	}
	if (g_status.infork == NO)
		ft_putendl_fd("exit", 1);
	i = check_exit(args->name);
	if (args->next != NULL)
		return (print_error("exit", ": too many arguments", 1));
	exit(i);
	return (0);
}
