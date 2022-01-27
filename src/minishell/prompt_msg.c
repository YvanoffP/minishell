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
	if (!new)
		return (NULL);
	new[0] = '~';
	return (new);
}

void	prompt_msg(t_mini *shell)
{
	char	*cwd;
	char	*final;
	char	*parsed_cwd;
	char	buff[4096];

	parsed_cwd = NULL;
	final = NULL;
	cwd = getcwd(buff, 4096);
	parsed_cwd = sub_path(cwd);
	if (shell->argv != NULL)
		free(shell->argv);
	final = ft_strjoin(parsed_cwd, " % ");
	free(parsed_cwd);
	shell->argv = readline(final);
	if (final != NULL)
		free(final);
}
