#include "../../inc/minishell.h"

int	is_w_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\r'
			|| c == '\n' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

int print_sep_error(char sep)
{
	write(1, "parse error near '", 18);
	write(1, &sep, 1);
	write(1, "'\n", 2);
	return (1);
}

int	is_sep(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int	catch_sep_err(char *argv)
{
	int	i;

	i = -1;
	while (argv[++i])
	{
		while (is_w_space(argv[i]))
			i++;
		if (is_sep(argv[i]))
			return (print_sep_error(argv[i]));
		while (!is_sep(argv[i]) && argv[i])
			i++;
	}
	return (0);
}

int	print_quote_err(void)
{
	write(1, "Error : found an unclosed quote or double quotes\n", 26);
	return (1);
}

int	catch_quote_err(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] == 39)
		{
			while (arg[i] != 39 || arg[i] != '\0')
				i++;
			if (arg[i] == 39)
				i++;
			else
				return (print_quote_err());
		}
		if (arg[i] == 34)
		{
			while (arg[i] != 34 || arg[i] != '\0')
				i++;
			if (arg[i] == 34)
				i++;
			else
				return (print_quote_err());
		}
	}
	return (0);
}

int	count_n_alloc_wrds(t_mini *shell)
{
	int	nb_wrd;
	int	i;

	if (catch_sep_err(shell->argv))
		return (1); // an error has been catched
	if (catch_quote_err(shell->argv))
		return (1);
	while (shell->argv[i])
	{
		alloc_wrd_til_sep(); // pay attention to " '
		copy_wrds(); // copy the strlen malloc'd words into the previos allocated ** array
		if (is_sep(shell->argv[i])) // gets 1 if it's on a sep
		{
			new_node(); // this node will be there to stock the sep
			copy_node(); // this will copy the sep into the node
			move_pointer_curr_node(); // move the current pointer of the lichain
			create_arg_node(); // this node will be there to stock the new passage in the while loop
			move_pointer_curr_node(); // move pointer again
		}
	}
	return (0);
}

void	split_arg(t_mini *shell)
{
	int	i;

	i = 0;
	if (count_n_alloc_wrds(shell))
		return ;
	while (is_w_space(shell->argv[i]))
		i++;


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
	else if (!ft_strcmp(shell->arg_split[0], UNSET))
		unset(shell->arg_split[1], env_list);
}
