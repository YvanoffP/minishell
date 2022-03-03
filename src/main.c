#include "minishell.h"

static void	destroy_childs(t_mini *shell)
{
	t_alloc	var;

	while (shell->child)
	{
		var.child = shell->child->next;
		while (shell->child->args)
		{
			var.temp = shell->child->args->next;
			free(shell->child->args->name);
			free(shell->child->args);
			shell->child->args = var.temp;
		}
		while (shell->child->redirection)
		{
			var.tmp = shell->child->redirection->next;
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
		free(shell->argv);
	shell->argv = NULL;
	if (shell->exec)
		free(shell->exec);
}

int main(int argc, char **argv, char **envp)
{
	t_mini	shell;
	t_env	*env_list;
	(void)argc;
	(void)argv;

	init_mini(&shell, &env_list);
	init_env(&env_list, envp);
	while (1)
	{
		run_signals(1);
		prompt_msg(&shell);
		working_history(&shell);
		if (ft_strcmp(shell.argv, ""))
		{
			if (parsing(&shell, &env_list))
				execution(&env_list, &shell);
			destroy(&shell);
		}
		// when wxit is catch find a way to break the while loop :)
	}
	exit_shell(&shell);
	return (0);
}
