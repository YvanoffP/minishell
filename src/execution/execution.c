#include "../../inc/minishell.h"

int	find_file(t_env **env_list)
{
	//This function will search file using PATH env variable
	//Need to receive arguments too

	t_env *tmp;
	char	**path;
	int		status;
	int		i;

	i = 0;
	//We need to set status to an int and track it at the end to check if all is ok
	//For this example we gonna use 100
	status = 100;
	tmp = search_in_list(env, "PATH");
	if (tmp == NULL)
		return (check_file());
	//We want to put all the path usr/bin/local:usr/bin:.... in a char ** array
	path = ft_split(tmp->var, ':');
	while (path[i] != NULL)
	{
		exec_file(env_list, path[i], &status);
		free(path[i++]);
	}
	free(path);
	return (status);
}

char	join_path_to_arg(char *path, char *arg)
{
	char	*tmp_path;
	char	*full_path;

	tmp_path = ft_strjoin(path, "/");
	full_path = ft_strjoin(tmp_path, arg);
	free(path_tmp);
	return (full_path);
}

void	exec_file(t_env **env_list, char *path, int *status)
{
	//Need to receive arguments too : ARG !

	struct stat	buf;
	char		*joined_path;

	buf.st_mode = 0;
	joined_path = join_path_to_arg(path, ARG)//TODO : Add to make function who join a path and command receive by user
	stat(joined_path, &buf);
	if ((buf.st_mode & S_IXUSR) > 0
		&& (buf.st_mode & S_IFREG) > 0 && *status == 100)
	{
			//Here we want to free the char * who stored the command, and str_dup the joined_path on this char *. And then send it to exec_program();
			*status = exec_program()
	}
	free(joined_path);
}

void	exec_program( , t_env **env_list)
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
		execve();
	//ELSE IF : we want to protect the failed fork
	else if (pid == -1)
		return ("Fork failed")
	
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
		return (f_status);
	}
	//We have to track success too, so we can define SUCCESS on an int or just return an int but both of them know the value of this int
	return (SUCCESS);
}

int	check_file(t_env **env_list)
{
	//this function need to receive arguments parsed in linked list (i guess)

	//This struct is available on Stat_Function file in Obsidian
	// buf is a pointer on the struc returned by stat functions
	struct stat	buf;

	//First argument of stat() is char *path, so the arg value stocked in the list
	//if stat() return -1, it means that the file was not found
	if (stat( ,&buf) == -1)
		return ("no such file or directory");
	//This line check if mode is stored with S_IFDIR, that means is not a file but a directory
	else if (buf.st_mode & S_IFDIR)
		return ("Is a directory");
	//This line check if permissiom of execute and search is available
	else if ((buf.st_mode & S_IXUSR) == 0)
		return ("Permission denied")
	//exec_file() had to receive the args too
	return (exec_program(, env_list))
}

int	check_path(t_env **env_list)
{
	//this function need to receive arguments parsed in linked list (i guess)

	int	status;

	//Here we have to check if the args start with "./"
	//STATUS : is an int who will track what is going on, so we have to check is value
	//when function return to see if all processes terminate correctly or no

	//IF we found "./", we have to check the file : path, permission, if the file
	// already exist etc
	if ()
		check_file();

	//ELSE : we have to find file using PATH environment variable 
	// then execute file using all path present in PATH variable
	else
	{
		find_file();
	}
	return (0);
}

void	execution(t_env **env_list)
{
	//In our case, execution() is called once parsing is "done", so we know that
	//our arguments start with "./" or just a script name
	//so we have to separate those 2 processes

	//We have to adapt the code with redirection
	//Once parsing is done, we have to treat args with those redirections
	//and make back_up using dup and dup2 function

	//All of our functions have to return int to track error or success operation

	//do_backup

	//treat redirection

	check_path(env_list);
}
