#include "../inc/minishell.h"

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
		prompt_msg();
		sleep(2);
	}
	exit_shell(&shell);
	return (0);
}
