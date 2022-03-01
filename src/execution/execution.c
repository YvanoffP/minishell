#include "../../inc/minishell.h"

int	print_error(char *str, char *msg, int ret)
{
	ft_putstr_fd("minishell: ", 2);
	if (str != NULL)
		ft_putstr_fd(str, 2);
	ft_putendl_fd(msg, 2);
	return (ret);
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

char	**lst_to_array(t_env **env_list)
{
	char	**ret;
	t_env	*tmp;
	int		i;

	tmp = *env_list;
	i = count_list(env_list);
	ret = (char **)malloc(sizeof(char *) * (i + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (tmp != NULL)
	{
		ret[i] = ft_strjoin(tmp->var, tmp->value);
		i++;
		tmp = tmp->next;
	}
	ret[i] = NULL;
	return (ret);
}

int	find_file(t_env **env_list, t_command *child)
{
	t_env *tmp;
	char	**path;
	int		status;
	int		i;

	i = 0;
	//We need to set status to an int and track it at the end to check if all is ok
	//For this example we gonna use 100
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

char	*join_path_to_arg(char *path, char *arg)
{
	char	*tmp_path;
	char	*full_path;

	tmp_path = ft_strjoin(path, "/");
	full_path = ft_strjoin(tmp_path, arg);
	free(tmp_path);
	return (full_path);
}

void	exec_file(t_command *child, t_env **env_list, char *path, int *status)
{
	//Need to receive arguments too : ARG !

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

int	count_args(t_built_args *lst)
{
	t_built_args	*tmp;
	int				i;

	tmp = lst;
	i = 0;
	while (tmp && tmp->next)
	{
		tmp = tmp->next;
		i++;
	
	}
	return (i);
}

char	**args_to_array(t_command *child)
{
	t_built_args	*tmp;
	char			**arg;
	int				i;

	tmp = child->args;
	i = count_args(tmp) + 1;
	arg = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	arg[i++] = ft_strdup(child->cmd);
	while (tmp != NULL)
	{
		arg[i++] = ft_strdup(tmp->name);
		tmp = tmp->next;
	}
	arg[i] = NULL;
	return (arg);
}

int	exec_program(t_command *child, t_env **env_list)
{
	int	pid;
	int	status;
	int	ret_status;

	pid = fork();
	ret_status = 0;

	//THINK ABOUT TRACKING ERROR !!!!!

	//We want to call execve if pid is == 0
	//Execve need our args stored in char ** and our list on char **, not on linked list
	//NOTE : EXECVE HAD TO BE PROTECT : if it return -1, an error occurs and we have to track it
	if (!pid)
	{
		if (execve(child->cmd, args_to_array(child), lst_to_array(env_list)) == -1)
			print_error(child->cmd, "Execve failed", -1);
		exit(0);
	}
	else if (pid == -1)
		return (print_error("fork: ", "Fork failed", -2));
	//ELSE : Fork success, we have to run on child process and wait return of this child
	// OPTIONS for waitpid is 0 : man tell that because waitpid behaviour is same as wait
	//if option is set on 0
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			ret_status = WEXITSTATUS(status);
		//Find a way to deal with different error, to stock the value of an error_int in f_status to return him
		else if (WIFSIGNALED(status))
		{
			//Here is saw a guy who add 128 + WTERMSIG but idk why for the moment
			ret_status =  WTERMSIG(status);
			if (WTERMSIG(status) == SIGQUIT)
				write(1, "Quit : 3\n", 8);
		}
		return (ret_status);
	}
	//We have to track success too, so we can define SUCCESS on an int or just return an int but both of them know the value of this int
	return (100);
}

int	check_file(t_env **env_list, t_command *child)
{
	struct stat	buf;

	//if stat() return -1, it means that the file was not found
	if (stat(child->cmd, &buf) == -1)
		return (print_error(child->cmd, ": No such file or directory", 1));
	//This line check if mode is stored with S_IFDIR, that means is not a file but a directory
	else if (buf.st_mode & S_IFDIR)
		return (print_error(child->cmd, ": Is a directory", 1));
	//This line check if permissiom of execute and search is available
	else if ((buf.st_mode & S_IXUSR) == 0)
		return (print_error(child->cmd, ": Permission denied", 1));
	return (exec_program(child, env_list));
}

int	check_path(t_env **env_list, t_command *child)
{
	int	status;

	//STATUS : is an int who will track what is going on, so we have to check is value
	//when function return to see if all processes terminate correctly or no

	//IF we found "./", we have to check the file : path, permission, if the file
	// already exist etc
	if (ft_strchr(child->cmd, '/') || child->cmd[0] == '.')
		return (check_file(env_list, child));
	//ELSE : we have to find file using PATH environment variable 
	// then execute file using all path present in PATH variable
	else
	{
		status = find_file(env_list, child);
		if (status != -100)
			return (status);
		return (print_error(child->cmd, ": command not found", -1));
	}
	return (0);
}

void	backup(int flag)
{
	static int	stdin;
	static int	stdout;
	static int	stderr;

	if (flag)
	{
		stdin = dup(STDIN_FILENO);
		stdout = dup(STDOUT_FILENO);
		stderr = dup(STDERR_FILENO);
	}
	else if (!flag)
	{
		dup2(stdin, 0);
		dup2(stdout, 1);
		dup2(stderr, 2);
	}
}

int	is_builtins(t_env **env_list, t_command *child)
{
	if (!ft_strcmp(child->cmd, EXPORT))
		export_func(env_list, child->args);
	else if (!ft_strcmp(child->cmd, ECHO_CMD))
		echo_func(child->args);
	else if (!ft_strcmp(child->cmd, UNSET))
		unset(child->args, env_list);
	else if (!ft_strcmp(child->cmd, CD))
		cd(child->args->name);
	else if (!ft_strcmp(child->cmd, ENV))
		env_func(env_list);
	else if (!ft_strcmp(child->cmd, PWD))
		pwd();
	else if (!ft_strcmp(child->cmd, EXIT))
		exit(0);
	else
		return (check_path(env_list, child));
	return (0);
}

int	great_than(int *fd, t_redir *redirection)
{
	*fd = open(redirection->file_name, O_CREAT | O_TRUNC | O_RDONLY | O_WRONLY, 0644);
	if ((*fd) < 0)
		return (1);
	dup2((*fd), STDOUT_FILENO);
	close((*fd));
	return (0);
}

int	less_than(int *fd, t_redir *redirection)
{
	*fd = open(redirection->file_name, O_RDONLY);
	if ((*fd) < 0)
		return (1);
	dup2((*fd), STDIN_FILENO);
	close((*fd));
	return (0);
}

int	db_great_than(int *fd, t_redir *redirection)
{
	*fd = open(redirection->file_name, O_CREAT | O_RDONLY | O_WRONLY | O_APPEND, 0644);
	if ((*fd) < 0)
		return (1);
	dup2((*fd), STDOUT_FILENO);
	close((*fd));
	return (0);
}

int	redirection(t_redir *redirection, int *my_fd)
{
	while (redirection != NULL)
	{
		if (redirection->type == LESS)
		{
			if (less_than(&my_fd[0], redirection))
				return (1);
		}
		else if (redirection->type == GREAT)
		{
			if (great_than(&my_fd[1], redirection))
				return (1);
		}
		else if (redirection->type == DB_GREAT)
		{
			if (db_great_than(&my_fd[1], redirection))
				return (1);
		}
		redirection = redirection->next;
	}
	return (0);
}

int	execution(t_env **env_list, t_mini *shell)
{
	int ret;
	int	*my_fd;

	//All of our functions have to return int to track error or success operation

	ret = 0;
	my_fd = malloc(sizeof(int) * 2);
	my_fd[0] = 0;
	my_fd[1] = 0;
	backup(1);
	if (shell->child->redirection)
	{
		if (redirection(shell->child->redirection, my_fd))
		{
			backup(0);
			return (1);
		}
	}
	if (shell->child->cmd == NULL && shell->child->redirection == NULL)
		return (print_error("\0", "command not found", -1));

	//On comptera le nb de cmd si > 1 alors on execute pipe
	//start

	if (shell->child->cmd != NULL)
		ret = is_builtins(env_list, shell->child);
	backup(0);
	return (ret);
}
