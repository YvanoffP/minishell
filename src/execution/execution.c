#include "../../inc/minishell.h"

char	*join_path_to_arg(char *path, char *arg)
{
	char	*tmp_path;
	char	*full_path;

	tmp_path = ft_strjoin(path, "/");
	full_path = ft_strjoin(tmp_path, arg);
	free(tmp_path);
	return (full_path);
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
			ret_status =  128 + WTERMSIG(status);
			if (WTERMSIG(status) == SIGQUIT)
				write(1, "Quit : 3\n", 8);
		}
		return (ret_status);
	}
	//We have to track success too, so we can define SUCCESS on an int or just return an int but both of them know the value of this int
	return (100);
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
		exit_func(child->args);
	else
		return (check_path(env_list, child));
	return (0);
}

int	execution(t_env **env_list, t_mini *shell)
{
	t_process *proc;

	proc = malloc(sizeof(t_process));	// BRING IT BABE
	proc->ret = 0;
	proc->my_fd[0] = 0;
	proc->my_fd[1] = 0;
	backup(1);
	if (shell->child->redirection)
	{
		if (redirection(shell->child->redirection, proc))
			return (backup(0));
	}
	if (shell->child->cmd == NULL && shell->child->redirection == NULL)
	{
		free(proc);
		return (print_error("\0", "command not found", 127));
	}
	if (shell->cmd_count > 1)
		proc->ret = pipe_my_ride(shell, proc, env_list);
	else if (shell->child->cmd != NULL)
		proc->ret = is_builtins(env_list, shell->child);
	backup(0);
//	free(proc);
	return (proc->ret);
}
