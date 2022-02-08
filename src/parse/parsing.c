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

int	print_quote_err(void)
{
	write(1, "Error : found an unclosed quote or double quotes\n", 26);
	return (1);
}

int	count_arr(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char **tab_dup(char **args, int	size)
{
	char **ret;
	int	i;

	i = -1;
	ret = (char **)malloc(sizeof(char *) * size + 1);
	if (!ret)
		return (NULL); // ERROR MALLOC CATCHED
	while (++i < size - 1)
		ret[i] = ft_strdup(args[i]);
	ret[i] = 0;
	return (ret);
}

void	realloc_arr(t_mini *shell)
{
	char	**tmp;

	if (shell->current->args == NULL)
	{
		shell->current->args = (char **)malloc(sizeof(char *) * 2);
		if (!shell->current->args)
			return ; // ERROR MALLOC CATCHED
		shell->current->args[0] = 0;
		shell->current->args[1] = 0;
		return ;
	}
	tmp = tab_dup(shell->current->args, count_arr(shell->current->args) + 1);
	free_array(shell->current->args);
	if (!tmp)
		return ; // ERROR MALLOC CATCHED
	shell->current->args = tab_dup(tmp, count_arr(tmp) + 1);
	free_array(tmp);
	if (!shell->current->args)
		return ; // ERROR MALLOC CATCHED
}

void	init_args(t_mini *shell)
{
	shell->first = malloc(sizeof(t_arg));
	shell->first->args = NULL;
	shell->first->next = NULL;
	shell->current = shell->first;
}

int	wrd_len(char *str, char sep, int *i)
{
	int	j;

	j = *i;
	while (str[j] != sep && str[j] && !is_sep(str[j]))
		j++;
	return (j - *i);
}

void	copy_wrd(t_mini *shell, int *i, int nb_wrd)
{
	int	wrd_size;


	wrd_size = wrd_len(shell->argv, ' ', i);
	// if it;s a ' or a ", copy until you find the closing one
	shell->current->args[nb_wrd] = ft_substr(shell->argv, *i, (size_t)wrd_size);
	*i += wrd_size;
	while (is_w_space(shell->argv[*i]) && shell->argv[*i] != '\0')
		*i += 1;
}

void	split_arg(t_mini *shell)
{
	int	i;
	int	nb_wrd;

	i = 0;
	init_args(shell);
	while (shell->argv[i])
	{
		nb_wrd = 0;
		while (!is_sep(shell->argv[i]) && shell->argv[i])
		{
			realloc_arr(shell);
			copy_wrd(shell, &i, nb_wrd);
			nb_wrd++;
		}
		//create new node
		//stock sep in new node
		//create new node initialisated @ NULL
	}
}

void	parsing(t_mini *shell, t_env **env_list)
{
	(void)env_list;
	if (!ft_strcmp(shell->argv, ""))
		return ;
	split_arg(shell);
	free_array(shell->current->args);
	exit(0);
	/*if (!ft_strcmp(shell->arg_split[0], CD))
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
		*/
}
