#include "../../inc/minishell.h"

char *sub_path(char *path)
{
	int		str_len;
	int		i;
	char	*new;

	str_len = ft_strlen(path);
	i = str_len;
	while (path[i] != '/')
		i--;
	new = ft_substr(path, i + 1, str_len);
	return (new);
}

void	prompt_msg(t_mini *shell)
{
	char	*cwd;
	char	*parsed_cwd;
	char	buff[4096];

	cwd = getcwd(buff, 4096);
	parsed_cwd = NULL;
	if (ft_strlen(cwd) == ft_strlen(shell->mini_cwd) &&
			!(ft_strncmp(cwd, shell->mini_cwd, ft_strlen(cwd))))
		ft_putstr_fd("~", 1);
	else
	{
		parsed_cwd = sub_path(cwd);
		ft_putstr_fd(parsed_cwd, 1);
	}
	ft_putstr_fd(" % ", 1);
	write(1, "\n", 1);
	if (parsed_cwd != NULL)
		free(parsed_cwd);
}
