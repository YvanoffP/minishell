#include "../../inc/minishell.h"

int	is_w_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\r' || c == '\n'
			|| c == '\v' || c == '\f')
		return (1);
	return (0);
}

int	is_sep(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int	lf_next_quote(char *str, char quoted)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != quoted || str[i] != '\0')
		i++;
	if (str[i] != quoted)
		return (1);
	else
		return (0);
}

int	check_n_save_str(t_mini *shell, char quoted)
{
	int i;

	i = -1;
	// create a new arg for all of this
	(*shell->argv)++;	// skips the first quote before finding the next quote
	if (!lf_next_quote(shell->argv, quoted))
	{
		write(1, "Error : found an unclosed quote or double quotes\n", 26);
		return (0);
	}
	while (*shell->argv != quoted)
	{
		INSERTNODEARGHERE[++i] = *shell->argv;		//copy content into struct
		(*shell->argv)++;
	}
	(*shell->argv)++;	//skips the last quote before going intop the parse again
	return (1);
}

int	save_til_space(t_mini *shell)
{
	int i;

	i = -1
	while (!is_w_space(*shell->argv) && *shell->argv)
	{
		INSERTNODEARGHERE[++i] = *shell->argv;		//copy content into struct
		(*shell->argv)++;
		if (*shell->argv == 39 || *shell->argv == 34)
		{
			if (!check_n_save_str(shell), *shell->argv)
				return (0);
		}
	}
	return (1);
}

void	split_args(t_mini *shell)
{
	while (*shell->argv)
	{
		while (is_w_space(*shell->argv))
			(*shell->argv)++;
		if (is_sep(*shell->argv))
		{
			write(1, "parse error near '", 18);
			write(1, *shell->argv, 1);
			write(1, "'\n", 2);
			return ;
		}
		while (!is_sep(*shell->argv) && *shell->argv)
		{
			if (*shell->argv == 39 || *shell->argv == 34)
			{
				if (!check_n_save_str(shell), *shell->argv)
					return ;
			}
			else
			{
				if (!save_til_space(shell))
					return ;
			}
			if (is_w_space(*shell->argv) && *shell->argv)	// I should create a skip w space func
				(*shell->argv)++;
		}
		if (*shell->argv == '\0')
			return ;
		// create a new node to store the separator
		// creare a new node for the next args to parse
		// We need to have a pointer to the first element of the arg nodes, so
		// we can continuously create new nodes and call it like
		// shell->node->value = 1231231 and never care about how many we
		// created while parsing
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
	else if (!ft_strcmp(shell->arg_split[0], UNSET))
		unset(shell->arg_split[1], env_list);
}
