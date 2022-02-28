#include "minishell.h"

int	cd(char *path)
{
	int	ret;

	ret = chdir(path);
	if (ret)
	{
		write(1, "cd: no such file or directory: ", 31);
		write(1, path, ft_strlen(path));
		write(1, "\n", 1);
		return (1);		//error detected
	}
	return (0);		//no error
}
