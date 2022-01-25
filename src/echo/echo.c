#include "../inc/minishell.h"

void	echo_func(char *str, int flag)
{
	// FLAG = 1 if -n || FLAG = 0 if not -n
	int	i;

	i = 0;
	if (!str && flag)
		return ;
	else if (!str && !flag)
	{
		write(1, "\n", 1);
		return ;
	}
	while (str[i] != '\0')
		write(1, &str[i++], 1);
	write(1, "\n", 1); // TODO : import flag for -n options
}
