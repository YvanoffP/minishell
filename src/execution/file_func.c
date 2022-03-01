#include "../../inc/minishell.h"

void	exec_file(t_command *child, t_env **env_list, char *path, int *status)
{
	struct stat	buf;
	char		*joined_path;

	buf.st_mode = 0;
	joined_path = join_path_to_arg(path, child->cmd);
	stat(joined_path, &buf);
	if ((buf.st_mode & S_IXUSR) > 0
		&& (buf.st_mode & S_IFREG) > 0 && *status == -100)
	{
			free(child->cmd);
			child->cmd = ft_strdup(joined_path);
			*status = exec_program(child, env_list);
	}
	free(joined_path);
}

int	error_file(t_redir *redirection)
{
	struct stat	buf;

	if (stat(redirection->file_name, &buf) == 0)
	{
		if (buf.st_mode & S_IFDIR)
			return (print_error(redirection->file_name, ": Is a directory", 1));
		else if ((buf.st_mode & S_IXUSR) == 0)
			return (print_error(redirection->file_name, ": Permission denied", 1));
	}
	return (print_error(redirection->file_name, ": No such file or directory", 1));
}

int	check_path(t_env **env_list, t_command *child)
{
	int	status;

	if (ft_strchr(child->cmd, '/') || child->cmd[0] == '.')
		return (check_file(env_list, child));
	else
	{
		status = find_file(env_list, child);
		if (status != -100)
			return (status);
		return (print_error(child->cmd, ": command not found", -1));
	}
	return (0);
}

int	check_file(t_env **env_list, t_command *child)
{
	struct stat	buf;

	if (stat(child->cmd, &buf) == -1)
		return (print_error(child->cmd, ": No such file or directory", 1));
	else if (buf.st_mode & S_IFDIR)
		return (print_error(child->cmd, ": Is a directory", 1));
	else if ((buf.st_mode & S_IXUSR) == 0)
		return (print_error(child->cmd, ": Permission denied", 1));
	return (exec_program(child, env_list));
}

int	find_file(t_env **env_list, t_command *child)
{
	t_env *tmp;
	char	**path;
	int		status;
	int		i;

	i = 0;
	status = -100;
	tmp = get_in_lst("PATH", env_list);
	if (tmp == NULL)
		return (check_file(env_list, child));
	path = ft_split(tmp->value, ':');
	while (path[i] != NULL)
	{
		exec_file(child, env_list, path[i], &status);
		free(path[i++]);
	}
	free(path);
	return (status);
}
