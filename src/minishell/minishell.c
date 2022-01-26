#include "../../inc/minishell.h"

void	init_mini(t_mini *shell)
{
	char	buff[4096];
	char	*cwd;

	cwd = getcwd(buff, 4096);
	shell->mini_cwd = sub_path(cwd);
}

void	exit_shell(t_mini *shell)
{
	free(shell->mini_cwd);
}
