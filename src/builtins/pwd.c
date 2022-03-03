#include "minishell.h"

void	pwd(void)
{
	char	*cwd;
	char	*parsed_cwd;
	char	buff[4096];

	cwd = getcwd(buff, 4096);
	if (cwd == NULL)
		write(1, "pwd command failed\n", 19);
	parsed_cwd = sub_path(cwd);
	write(1, parsed_cwd, ft_strlen(parsed_cwd));
	write(1, "\n", 1);
	if (parsed_cwd)
		free(parsed_cwd);
}
