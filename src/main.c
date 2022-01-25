#include "../inc/minishell.h"

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	prompt_msg(void)
{
	char	*cwd;
	char	buff[4096];

	cwd = getcwd(buff, 4096);
	ft_putstr_fd(cwd, 1);
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	//init the minishell here
	while (1)
	{
		prompt_msg();
		sleep(1);
	}
	return (0);
}
