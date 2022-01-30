#include "../../inc/minishell.h"

void	working_history(t_mini *shell)
{
	add_history(shell->argv);
	if (shell->fd_history == 0)
		shell->fd_history = open("./.history_cmd", O_APPEND | O_WRONLY);
	if (shell->fd_history == -1)
		printf("Error: open file failed");
	else
	{
		write(shell->fd_history, shell->argv, ft_strlen(shell->argv));
		write(shell->fd_history, "\n", 1);
	}
}
