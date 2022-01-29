#include "minishell.h"

void	echo_func(char *str, char *str2)
{
	int	i;

	i = 0;
	if (!str && !str2)
		return ;
	if (str2 == NULL) // MEANS NO FLAG
	{
		while (str[i] != '\0')
			write(1, &str[i++], 1);
		write(1, "\n", 1);
		return ;
	}
	else if (!ft_strcmp(str, "-n"))
	{
		while (str2[i] != '\0')
			write(1, &str2[i++], 1);
		return ;
	}
	write(1, "\n", 1);
}
