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
	write(1, "Error : found an unclosed quote or double quotes\n", 49);
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
	t_arg	*args;

	args = malloc(sizeof(t_arg));
	args->args = NULL;
	args->next = NULL;
	shell->first = args;
	shell->current = args;
}

int	wrd_len(char *str, char sep, int *i)
{
	int	j;

	j = *i;
	while (str[j] != sep && str[j] && !is_sep(str[j]))
		j++;
	if (str[j] == '\0' && sep != ' ')
		return (-1);
	return (j - *i);
}

void	skip_w_space(char *str, int *i)
{
	while (is_w_space(str[*i]))
		*i += 1;
}

int	*catch_quote(char const *s, unsigned int start, int len)
{
	int i;
	char sep;
	int flag;
	int j;
	int *quotes;
	int	nb_quotes;

	quotes = malloc(sizeof(int) * 29);
	flag = 0;
	j = 0;
	i = 0;
	nb_quotes = 0;
	while (i < len && s[start + i])
	{
		if ((s[start + i] == 34 || s[start + i] == 39) && flag == 0)
		{
			flag = 1;
			sep = s[start + i];
			quotes[j++] = start + i;
			nb_quotes++;
		}
		else if (s[start + i] == sep && flag == 1)
		{
			flag = 0;
			quotes[j++] = start + i;
			nb_quotes++;
		}
		i++;
	}
	quotes[j] = -1;
	quotes[29] = nb_quotes;
	return (quotes);
}

char	*cpy_str(char const *s, int start, int len)
{
	char	*ret;
	int	i;
	int	j;
	int	count;
	int	*quotes;
	int	cpy_count;

	cpy_count = 0;
	j = 0;
	count = 0;
	i = ft_strlen(s);
	if (!s)
		return (NULL);
	if ((int)start > i)
		return (ft_strdup(""));
	quotes = catch_quote(s, start, len);
	if (i - start < len)
		len = i - (int)start;
	if (quotes[29] % 2 == 1)
	{
		write(1, "Error : found an unclosed quote or double quotes\n", 49);
		return (NULL);
	}
	ret = (char *)malloc(sizeof(char) * (len + 1) - quotes[29]);
	if (ret == NULL)
		return (NULL);
	while (count < len)
	{
		if (count + start == quotes[j] && quotes[j] != -1)
		{
			j++;
			count++;
		}
		ret[cpy_count] = s[start + count];
		count++;
		cpy_count++;
	}
	ret[cpy_count] = '\0';
	free(quotes);
	return (ret);
}

int	copy_wrd(t_mini *shell, int *i, int nb_wrd)
{
	int		wrd_size;
	char	sep;

	if (!shell->argv[*i])
		return (0);
	skip_w_space(shell->argv, i);
	if (shell->argv[*i] == 34 || shell->argv[*i] == 39)
	{
		sep = shell->argv[*i];
		*i += 1;
		wrd_size = wrd_len(shell->argv, sep, i);
		if (wrd_size == -1)
			return (print_quote_err());
		if (wrd_size == 0)
		{
			*i += 1;
			return (-1);
		}
		shell->current->args[nb_wrd] = ft_substr(shell->argv, *i, (int)wrd_size);
		*i += wrd_size;
		*i += 1;
		return (0);
    }
	else
	{
		wrd_size = wrd_len(shell->argv, ' ', i);
		shell->current->args[nb_wrd] = cpy_str(shell->argv, *i, (int)wrd_size);
		if (shell->current->args[nb_wrd] == NULL)
			return (1);
		*i += wrd_size;
		while (is_w_space(shell->argv[*i]) && shell->argv[*i] != '\0')
			*i += 1;
		return (0);
	}
	return (1);
}

char	*add_sep_to_node(t_mini *shell, int *i)
{
	int	j;
	char	*ret;

	j = *i;
	while (shell->argv[*i] == '|' || shell->argv[*i] == '<' || shell->argv[*i] == '>')
		*i += 1;
	ret = ft_substr(shell->argv, j, (*i - j));
	if (!ret)
		return (NULL);
	return (ret);
}

void	add_sep_to_lst(t_mini *shell, int *i)
{
	t_arg	*new;

	new = malloc(sizeof(t_arg));
	if (new)
	{
		new->args = malloc(sizeof(char *) * 2);
		new->args[0] = add_sep_to_node(shell, i);
		new->args[1] = NULL;
		new->next = NULL;
		if (shell->current)
		{
			while (shell->current && shell->current->next)
				shell->current = shell->current->next;
			shell->current->next = new;
			shell->current = new;
		}
		else
			shell->current = new;
	}
}

void	create_n_add_empty_node(t_mini *shell)
{
	t_arg	*new;

	new = malloc(sizeof(t_arg));
	if (new)
	{
		new->args = NULL;
		new->next = NULL;
		while (shell->current && shell->current->next)
			shell->current = shell->current->next;
		shell->current->next = new;
		shell->current = new;
	}
	else
		shell->current = new;
}

void	split_arg(t_mini *shell)
{
	int	i;
	int	nb_wrd;
	int ret;

	i = 0;
	init_args(shell);
	while (shell->argv[i])
	{
		nb_wrd = 0;
		while (!is_sep(shell->argv[i]) && shell->argv[i])
		{
			realloc_arr(shell);
			ret = copy_wrd(shell, &i, nb_wrd);
			while (ret == -1)
				ret = copy_wrd(shell, &i, nb_wrd);
			if (ret == 1)
				return ;
			nb_wrd++;
		}
		//START LIST
		skip_w_space(shell->argv, &i);
		if (is_sep(shell->argv[i]) && shell->argv[i])
		{
			add_sep_to_lst(shell, &i);
			skip_w_space(shell->argv, &i);
			if (!shell->argv[i] || is_sep(shell->argv[i]))
			{
				printf("Error : no args after after sep or two consecutive sep\n");
				return ;
			}
			create_n_add_empty_node(shell);
		}
		//DESTROY LIST
	}
}

void	destroy_arg_lst(t_mini *shell)
{
	//Those free functions have to be tested with valgrind because leaks seems not ok
	//With or without the two last free, leaks commands display no leak
	//but if we print shell->first->args after boucle while, shell->first->args contains
	//the last argument

	t_arg	*tmp;

	while (shell->first && shell->first->next)
	{
		tmp = shell->first->next;
		free_array(shell->first->args);
		free(shell->first);
		shell->first = tmp;
	}
	free_array(shell->first->args);
	free(shell->first);
}

void	parsing(t_mini *shell, t_env **env_list)
{
	(void)env_list;
	if (!ft_strcmp(shell->argv, ""))
		return ;
	split_arg(shell);
	destroy_arg_lst(shell);
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
