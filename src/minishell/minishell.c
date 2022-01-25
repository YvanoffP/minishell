#include "../../inc/minishell.h"

void	init_mini(t_mini *shell)
{
	char	buff[4096];

	shell->mini_cwd = getcwd(buff, 4096);
}
