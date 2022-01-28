#include "minishell.h"

void	handler(int sig)
{
	if (sig == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
}
