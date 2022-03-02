#include "minishell.h"

void	destroy(t_mini *shell)
{
	t_built_args	*tmp;
	t_redir			*temp;
	t_command		*tempo;

	while (shell->child)
	{
		tempo = shell->child->next;
		while (shell->child->args)
		{
			tmp = shell->child->args->next;
			free(shell->child->args->name);
			free(shell->child->args);
			shell->child->args = tmp;
		}
		while (shell->child->redirection)
		{
			temp = shell->child->redirection->next;
			free(shell->child->redirection->file_name);
			free(shell->child->redirection);
			shell->child->redirection = temp;
		}
		free(shell->child->cmd);
		free(shell->child);
		shell->child = tempo;
	}
	if (shell->argv)
		free(shell->argv);
	shell->argv = NULL;
}

int main(int argc, char **argv, char **envp)
{
	t_mini	shell;
	t_env	*env_list;
	(void)argc;
	(void)argv;

	init_mini(&shell, &env_list);
	init_env(&env_list, envp);
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	while (1)
	{
		prompt_msg(&shell);
		working_history(&shell);
		if (ft_strcmp(shell.argv, ""))
		{
			parsing(&shell, &env_list);
			execution(&env_list, &shell);
			destroy(&shell);
		}
	}
	exit_shell(&shell);
	return (0);
}
