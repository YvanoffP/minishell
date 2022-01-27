#include "../../inc/minishell.h"

char *sub_path(char *path)
{
	int		str_len;
	int		i;
	int		slash_count;
	char	*new;
	char	*final;

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
	final = ft_strjoin(new, " % ");
	free(new);
	return (final);
}

void	prompt_msg(t_mini *shell)
{
	char	*cwd;
	char	*parsed_cwd;
	char	buff[4096];

	cwd = getcwd(buff, 4096);
	parsed_cwd = NULL;
	parsed_cwd = sub_path(cwd);
	if (shell->argv != NULL)
		free(shell->argv);
	shell->argv = readline(parsed_cwd);
	if (parsed_cwd != NULL)
		free(parsed_cwd);
}
