#include "../inc/minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_mini	shell;
	(void)argc;
	(void)argv;

	init_mini(&shell);
	while (1)
	{
		prompt_msg(&shell);
		// TODO : Free shell->argv after using it or before calling prompt
		// message again
	}
	exit_shell(&shell);
	return (0);
}


//TODO : Call envp for env_function : env_func(envp);
