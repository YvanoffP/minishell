#include "../../inc/minishell.h"

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

int	find_file(t_env **env_list, t_mini *shell)
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
		return (check_file(env_list, shell));
	path = ft_split(tmp->value, ':');
	while (path[i] != NULL)
	{
		exec_file(shell, env_list, path[i], &status);
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

void	exec_file(t_mini *shell, t_env **env_list, char *path, int *status)
{
	//Need to receive arguments too : ARG !

	struct stat	buf;
	char		*joined_path;

	buf.st_mode = 0;
	joined_path = join_path_to_arg(path, shell->current->args[0]); 
	stat(joined_path, &buf);
	if ((buf.st_mode & S_IXUSR) > 0
		&& (buf.st_mode & S_IFREG) > 0 && *status == -100)
	{
			free(shell->current->args[0]);
			shell->current->args[0] = ft_strdup(joined_path);
			*status = exec_program(shell, env_list);
	}
	free(joined_path);
}

int	exec_program(t_mini *shell, t_env **env_list)
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
		execve(shell->current->args[0], shell->current->args, lst_to_array(env_list));
	//ELSE IF : we want to protect the failed fork
	else if (pid == -1)
		return (str_error("Fork failed", 0));
	
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

int	check_file(t_env **env_list, t_mini *shell)
{
	struct stat	buf;

	//if stat() return -1, it means that the file was not found
	if (stat(shell->current->args[0], &buf) == -1)
		return (str_error("no such file or directory", 0));
	//This line check if mode is stored with S_IFDIR, that means is not a file but a directory
	else if (buf.st_mode & S_IFDIR)
		return (str_error("Is a directory", 0));
	//This line check if permissiom of execute and search is available
	else if ((buf.st_mode & S_IXUSR) == 0)
		return (str_error("Permission denied", 0));
	return (exec_program(shell, env_list));
}

int	check_path(t_env **env_list, t_mini *shell)
{
	int	status;

	//STATUS : is an int who will track what is going on, so we have to check is value
	//when function return to see if all processes terminate correctly or no

	//IF we found "./", we have to check the file : path, permission, if the file
	// already exist etc
	if (ft_strchr(shell->current->args[0], '/') || shell->current->args[0][0] == '.')
		return (check_file(env_list, shell));
	//ELSE : we have to find file using PATH environment variable 
	// then execute file using all path present in PATH variable
	else
	{
		status = find_file(env_list, shell);
		if (status != -100)
			return (status);
		return (str_error("command not found\n", 0));
	}
	return (0);
}

int	is_builtins(t_env **env_list, t_mini *shell)
{
	if (!ft_strcmp(shell->current->args[0], EXPORT))
		export_func(env_list, shell);
	else if (!ft_strcmp(shell->current->args[0], ECHO_CMD))
		echo_func(shell);
	else if (!ft_strcmp(shell->current->args[0], UNSET))
		unset(shell, env_list);
	else if (!ft_strcmp(shell->current->args[0], CD))
		cd(shell->current->args[1]);
	else if (!ft_strcmp(shell->current->args[0], ENV))
		env_func(env_list);
	else if (!ft_strcmp(shell->current->args[0], PWD))
		pwd();
	else if (!ft_strcmp(shell->current->args[0], EXIT))
		exit(0);
	else
		return (check_path(env_list, shell));
	return (0);
}

int	execution(t_env **env_list, t_mini *shell)
{
	int ret;

	//We have to adapt the code with redirection
	//Once parsing is done, we have to treat args with those redirections
	//and make back_up using dup and dup2 function

	//All of our functions have to return int to track error or success operation

	//do_backup ???

	//treat redirection
	ret = is_builtins(env_list, shell);
	return (ret);
}
