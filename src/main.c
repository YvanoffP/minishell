/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypetruzz <2befreed@student.42lausanne.ch>  +#+  +:+       +#+        */
/*   And: tpauvret                                 +#+   +:+      +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 23:13:46 by ypetruzz          #+#    #+#             */
/*   Updated: 2022/03/03 23:13:46 by ypetruzz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_inputrc(void)
{
	int		fd;
	int		ret;
	char	*buf;
	char	*home;

	ret = 0;
	fd = 0;
	buf = NULL;
	home = getenv("HOME");
	home = ft_strjoin(home, "/.inputrc");
	fd = open(home, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	ret = read(fd, buf, 100);
	if (ret == 0)
		write(fd, "set echo-control-characters Off",
			ft_strlen("set echo-control-characters Off"));
	free(home);
}

static void	destroy_childs(t_mini *shell)
{
	t_alloc	var;

	while (shell->child != NULL)
	{
		var.child = shell->child->next;
		while (shell->child->args)
		{
			var.temp = shell->child->args->next;
			if (shell->child->args->name)
				free(shell->child->args->name);
			free(shell->child->args);
			shell->child->args = var.temp;
		}
		while (shell->child->redirection)
		{
			var.tmp = shell->child->redirection->next;
			if (shell->child->redirection->file_name)
				free(shell->child->redirection->file_name);
			free(shell->child->redirection);
			shell->child->redirection = var.tmp;
		}
		free(shell->child->cmd);
		free(shell->child);
		shell->child = var.child;
	}
}

static void	destroy(t_mini *shell)
{
	destroy_childs(shell);
	if (shell->argv)
	{
		free(shell->argv);
		shell->argv = NULL;
	}
	shell->argv = NULL;
	if (shell->exec)
	{
		free(shell->exec);
		shell->exec = NULL;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	shell;
	t_env	*env_list;
	t_errs	*err;

	if (argc > 1)
		return (str_error("Too many arguments", 0));
	(void)argv;
	err = malloc(sizeof(t_errs));
	init_mini(&shell, &env_list);
	init_env(&env_list, envp);
	while (1)
	{
		run_signals(1);
		prompt_msg(&shell);
		if (shell.argv == NULL)
			break ;
		working_history(&shell);
		if (ft_strcmp(shell.argv, ""))
		{
			if (parsing(&shell, &env_list))
			{
				init_errs(err);
				g_status.status = process_cmd(&env_list, &shell, err);
			}
			destroy(&shell);
		}
	}
	exit_shell(&shell);
	return (0);
}
