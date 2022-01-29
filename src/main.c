#include "minishell.h"

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
		parsing(&shell, &env_list);
		destroy_arg(&shell);
		// TODO : Free shell->argv after using it or before calling prompt
		// message again
	}
	exit_shell(&shell);
	return (0);
}
