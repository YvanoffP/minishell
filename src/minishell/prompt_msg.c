#include "../../inc/minishell.h"

char *sub_path(char *path)
{
	int		str_len;
	int		i;
	int		slash_count;
	char	*new;

	str_len = ft_strlen(path);
	slash_count = 1;
	i = 1;
	while (path[i] && slash_count != 3)
	{
		if (path[++i] == '/')
			slash_count++;
	}
	if (slash_count == 2)
		new = malloc(sizeof(char));
	else
		new = ft_substr(path, i - 1, str_len);
	new[0] = '~';
	return (new);
}

void	prompt_msg(void)
{
	char	*cwd;
	char	*parsed_cwd;
	char	buff[4096];

	cwd = getcwd(buff, 4096);
	parsed_cwd = NULL;
	parsed_cwd = sub_path(cwd);
	ft_putstr_fd(parsed_cwd, 1);
	ft_putstr_fd(" % ", 1);
	write(1, "\n", 1);
	if (parsed_cwd != NULL)
		free(parsed_cwd);
}
