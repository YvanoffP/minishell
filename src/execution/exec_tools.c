/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypetruzz <ypetruzz@student.42lausanne.ch>  +#+  +:+       +#+        */
/*   And: tpauvret                                 +#+   +:+      +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 23:13:46 by ypetruzz          #+#    #+#             */
/*   Updated: 2022/03/03 23:13:46 by ypetruzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**args_to_array(t_command *child)
{
	t_built_args	*tmp;
	char			**arg;
	int				i;

	tmp = child->args;
	i = count_args(tmp) + 1;
	arg = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	arg[i++] = ft_strdup(child->cmd);
	while (tmp != NULL)
	{
		arg[i++] = ft_strdup(tmp->name);
		tmp = tmp->next;
	}
	arg[i] = NULL;
	return (arg);
}

int	backup(int flag)
{
	static int	stdin;
	static int	stdout;
	static int	stderr;

	if (flag)
	{
		stdin = dup(STDIN_FILENO);
		stdout = dup(STDOUT_FILENO);
		stderr = dup(STDERR_FILENO);
	}
	else if (!flag)
	{
		dup2(stdin, 0);
		dup2(stdout, 1);
		dup2(stderr, 2);
	}
	return (1);
}

int	count_args(t_built_args *lst)
{
	t_built_args	*tmp;
	int				i;

	tmp = lst;
	i = 0;
	while (tmp && tmp->next)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

int	print_error(char *str, char *msg, int ret)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (str != NULL)
		ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	return (ret);
}

char	**lst_to_array(t_env **env_list)
{
	char	**ret;
	t_env	*tmp;
	int		i;

	tmp = *env_list;
	i = count_list(env_list);
	ret = (char **)malloc(sizeof(char *) * (i + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (tmp != NULL)
	{
		ret[i] = ft_strjoin(tmp->var, tmp->value);
		i++;
		tmp = tmp->next;
	}
	ret[i] = NULL;
	return (ret);
}
