/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypetruzz <ypetruzz@student.42lausanne.ch>  +#+  +:+       +#+        */
/*   And: tpauvret                                 +#+   +:+      +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 23:13:46 by ypetruzz          #+#    #+#             */
/*   Updated: 2022/03/03 23:13:46 by ypetruzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_error_cd(char *str, char *msg, char *error, int ret)
{
	ft_putstr_fd("minishell: ", 2);
	if (str != NULL)
		ft_putstr_fd(str, 2);
	ft_putstr_fd(msg, 2);
	ft_putendl_fd(error, 2);
	return (ret);
}

int	cd(t_built_args *args)
{
	int	ret;

	ret = 0;
	if (args)
		ret = chdir(args->name);
	else
		chdir(getenv("HOME"));
	if (ret)
		return (print_error_cd("cd: ", args->name, ": No such file or directory", 1));
	return (0);
}
