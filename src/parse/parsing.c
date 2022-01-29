#include "../../inc/minishell.h"

void	destroy_arg(t_mini *shell)
{
	int	i;

	i = -1;
	while (shell->arg_split[++i] != NULL)
	{
		free(shell->arg_split[i]);
		shell->arg_split[i] = NULL;
	}
	shell->argv = NULL;
}

int	next_space_i(int start, char *str)
{
	if ((int)ft_strlen(str) == start || str[start] == '\0')
		return (-1);
	while (str[start] != ' ' && str[start] != '\0')
		start++;
	return (start);
}

char	*trim_arg(int from, int to, char *str)
{
	char *ret;
	int		i;

	i = 0;
	ret = malloc(sizeof(char) * (to - from) + 1);
	while (from != to)
	{
		ret[i] = str[from];
		from++;
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

void	split_arg(t_mini *shell)
{
	int	from;
	int	to;
	int	i;

	from = 0;
	to = 0;
	i = 0;
	while (to != -1)
	{
		to = next_space_i(from, shell->argv);
		while (to == from)
			to = next_space_i(++from, shell->argv);
		if (to == -1)
			break ;
		shell->arg_split[i++] = trim_arg(from, to, shell->argv);
		from = to + 1;
	}
}

void	parsing(t_mini *shell, t_env **env_list)
{
	if (!ft_strcmp(shell->argv, ""))
		return ;
	split_arg(shell);
	if (!ft_strcmp(shell->arg_split[0], CD))
		cd(shell->arg_split[1]);
	else if (!ft_strcmp(shell->arg_split[0], ECHO_CMD))
		echo_func(shell->arg_split[1], shell->arg_split[2]);
	else if (!ft_strcmp(shell->argv, ENV))
		env_func(env_list);
	else if (!ft_strcmp(shell->arg_split[0], EXPORT))
		export_func(env_list, shell->arg_split[1]);
	else if (!ft_strcmp(shell->arg_split[0], EXIT))
		exit(0);
	else if (!ft_strcmp(shell->arg_split[0], PWD))
		pwd();
//	else if (shell->arg_split[0], UNSET))
//		unset();
}
