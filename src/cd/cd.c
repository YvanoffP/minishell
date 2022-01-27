#include "../../inc/minishell.h"

int	cd(char *path)
{
	int	ret;

	ret = chdir(path);
	if (ret)
		return (1);		//error detected
	return (0);		//no error
}
