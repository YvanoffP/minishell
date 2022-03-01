#include "minishell.h"

int	cd(char *path)
{
	int	ret;

	ret = chdir(path);
	if (ret)
		return (print_error("cd: no such file or directory: ", path, 1));
	return (0);
}
