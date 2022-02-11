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

int	have_a_dollar(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char *find_env_var(char *str, int *i, t_env **env_list)
{
	char *name;
	int	j;
	t_env	*list;

	*i += 1;
	j = *i;
	list = *env_list;
	while (!is_w_space(str[*i]) && str[*i])
		*i += 1;
	name = ft_substr(str, j, (*i - j));
	while (ft_strcmp(name, list->var) && list->next != NULL)
		list = list->next;
	if (ft_strcmp(name, list->var))
	{
		free(name);
		return (NULL);
	}
	free(name);
	name = ft_strdup(list->value);
	*i -= 1;
	return (name);
}

char *append(char *ret, char *tmp, char *value)
{
	char *old_ret;
	char *new_ret;

	if (!value && !ret)
		return (ft_strdup(tmp));
	else if (!value && ret && tmp)
		return (ft_strjoin(ret, tmp));
	else if (value && !ret)
		return (ft_strjoin(tmp, value));
	else if (!value && ret && !tmp)
		return (ret);
	else if (value && ret && !tmp)
		return (ft_strjoin(ret, value));
	else
	{
		old_ret = ft_strdup(ret);
		free(ret);
		ret = ft_strjoin(tmp, value);
		new_ret = ft_strjoin(old_ret, ret);
		free(old_ret);
		free(ret);
	}
	return (new_ret);
}

char *replace_dollars(char *str, t_env **env_list)
{
	int	i;
	int	j;
	char *ret;
	char *tmp;
	char *value;

	i = 0;
	j = 0;
	ret = NULL;
	tmp = NULL;
	value = NULL;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (!i)
				tmp = ft_substr(str, j + 1, i - j);
			value = find_env_var(str, &i, env_list);
			if (!value)
				ret = append(ret, tmp, value);
			else
			{
				ret = append(ret, tmp, value);
				free(tmp);
				free(value);
				tmp = NULL;
				value = NULL;
			}
			j = i;
		}
		while (str[i] && str[i] != '$')
			i++;
		tmp = ft_substr(str, j + 1, i - j - 1);
		ret = append(ret, tmp, value);
		free(tmp);
		tmp = NULL;
	}
	return (ret);
}

char	*cpy_str(char const *s, int start, int len, t_env **env_list)
{
	char	*ret;
	char	*final;
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
	if (have_a_dollar(ret))
	{
		final = replace_dollars(ret, env_list);
		if (final == NULL)
			//Variable pas trouvee, faire qqch
		free(ret);
		return (final);
	}
	free(quotes);
	return (ret);
}

int	copy_wrd(t_mini *shell, int *i, int nb_wrd, t_env **env_list)
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
		shell->current->args[nb_wrd] = cpy_str(shell->argv, *i, (int)wrd_size, env_list);
		*i += wrd_size;
		*i += 1;
		return (0);
    }
	else
	{
		wrd_size = wrd_len(shell->argv, ' ', i);
		shell->current->args[nb_wrd] = cpy_str(shell->argv, *i, (int)wrd_size, env_list);
		if (shell->current->args[nb_wrd] == NULL)
			return (1);
		*i += wrd_size;
		while (is_w_space(shell->argv[*i]) && shell->argv[*i] != '\0')
			*i += 1;
		return (0);
	}
	return (1);
}

void	split_arg(t_mini *shell, t_env **env_list)
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
			ret = copy_wrd(shell, &i, nb_wrd, env_list);
			while (ret == -1)
				ret = copy_wrd(shell, &i, nb_wrd, env_list);
			if (ret == 1)
				return ;
			nb_wrd++;
		}
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
	}
}

void	parsing(t_mini *shell, t_env **env_list)
{
	if (!ft_strcmp(shell->argv, ""))
		return ;
	split_arg(shell, env_list);
	if (!ft_strcmp(shell->first->args[0], EXPORT))
		export_func(env_list, shell->first->args[1]);
	else if (!ft_strcmp(shell->first->args[0], ECHO_CMD))
		echo_func(shell->first->args[1], NULL);
	else if (!ft_strcmp(shell->first->args[0], EXIT))
		exit(0);
	/*if (!ft_strcmp(shell->arg_split[0], CD))
		cd(shell->arg_split[1]);
	else if (!ft_strcmp(shell->argv, ENV))
		env_func(env_list);
	else if (!ft_strcmp(shell->arg_split[0], EXPORT))
		export_func(env_list, shell->arg_split[1]);
	else if (!ft_strcmp(shell->arg_split[0], PWD))
		pwd();
	else if (!ft_strcmp(shell->arg_split[0], UNSET))
		unset(shell->arg_split[1], env_list);
		*/
}
