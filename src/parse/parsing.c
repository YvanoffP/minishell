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

void	skip_w_space(char *str, int *i)
{
	while (is_w_space(str[*i]))
		*i += 1;
}

int	have_a_dollar(char *str, int i)
{
	while (str[i] != 34)
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
	while (!is_w_space(str[*i]) && str[*i] && str[*i] != '$' && str[*i] != 34 && str[*i] != 39)
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
//	*i -= 1;
	return (name);
}

char *append(char *ret, char *tmp, char *value)
{
	if (!value && !ret && tmp)
		return (ft_strdup(tmp));
	else if (!value && ret && tmp)
		return (ft_strjoin(ret, tmp));
	else if (value && !ret && tmp)
		return (ft_strjoin(tmp, value));
	else if (!value && ret && !tmp)
		return (ret);
	else if (value && ret && !tmp)
		return (ft_strjoin(ret, value));
	else if (value && !ret && !tmp)
		return (ft_strdup(value));
	return (NULL);
}

char *replace_dollars(char *str, t_env **env_list, int i, int flag)
{
	int	j;
	char *ret;
	char *tmp;
	char *value;

	j = i;
	ret = NULL;
	value = NULL;
	tmp = NULL;
	if (i != 0)
		tmp = ft_substr(str, 0, i);
	while (str[i] != 34 && str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == 34 || str[i + 1] == '\0')
				break ;
			value = find_env_var(str, &i, env_list);
			if (!value)
			{
				ret = append(ret, tmp, value);
				free(tmp);
				tmp = NULL;
			}
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
		while (str[i] != 34 && str[i] != '$' && str[i])
			i++;
		if (flag)
		{
			while (str[i])
				i++;
		}
		if (i != j)
		{
			value = ft_substr(str, j, i - j);
			ret = append(ret, tmp, value);
			free(tmp);
			free(value);
			tmp = NULL;
			value = NULL;
		}
	}
	if (i < (int)ft_strlen(str))
	{
		tmp = ft_strdup(ret);
		value = ft_substr(str, i, ft_strlen(str) - i);
		free(ret);
		ret = NULL;
		ret = ft_strjoin(tmp, value);
		free(tmp);
		free(value);
		tmp = NULL;
		value = NULL;
	}
	return (ret);
}

void	skip_quote(char *str, int *i)
{
	//Reste a proteger du nb impair de quote si c'est necessaire
	//Sinon le compte est mauvais

	if (str[*i] == 34 || str[*i] == 39)
	{
		if (str[*i] == 34)
		{
			*i += 1;
			while (str[*i] != 34 && str[*i])
				*i += 1;
			if (!str[*i])
				return ;
		}
		else if (str[*i] == 39)
		{
			*i += 1;
			while (str[*i] != 39 && str[*i])
				*i += 1;
			if (!str[*i])
				return ;
		}
	}
}

int	count_sep(char *str)
{
	int	i;
	int	nb_sep;

	i = 0;
	nb_sep = 0;
	while (str[i])
	{
		skip_quote(str, &i);
		if (str[i] == '|' || str[i] == '<' || str[i] == '>')
			nb_sep++;
		i++;
	}
	return (nb_sep);
}

int	count_space(char *str)
{
	int	i;
	int	nb_space;

	i = 0;
	nb_space = 0;
	while (str[i])
	{
		skip_quote(str, &i);
		if (is_w_space(str[i]))
		{
			nb_space++;
			skip_w_space(str, &i);
			i--;
		}
		i++;
	}
	return (nb_space);
}

int	*parse_sep(char *str)
{
	int	nb_sep;
	int	*ind_sep;
	int	i;
	int	j;

	i = 0;
	j = 0;
	nb_sep = count_sep(str);
	ind_sep = malloc(sizeof(int) * nb_sep + 1);
	if (!ind_sep)
		return (NULL);
	while (str[i])
	{
		skip_quote(str, &i);
		if (is_sep(str[i]))
			ind_sep[j++] = i;
		i++;
	}
	ind_sep[j] = 0;
	return (ind_sep);
}

int	*parse_space(char *str)
{
	int	nb_space;
	int	*ind_space;
	int	i;
	int	j;

	i = 0;
	j = 0;
	nb_space = count_space(str);
	ind_space = malloc(sizeof(int) * nb_space + 1);
	if (!ind_space)
		return (NULL);
	ind_space[nb_space] = 0;
	while (str[i])
	{
		skip_quote(str, &i);
		if (is_w_space(str[i]))
		{
			ind_space[j++] = i;
			skip_w_space(str, &i);
			i--;
		}
		i++;
	}
	return (ind_space);
}

int	count_missing_space(char *str, int *sep)
{
	int	i;
	int	*ptr;
	int	missing_space;

	missing_space = 0;
	i = 0;
	ptr = sep;
	while (*ptr)
	{
		i = *ptr;
		if (is_w_space(str[i - 1]))
			missing_space++;
		if (is_w_space(str[i + 1]))
			missing_space++;
		ptr++;
	}
	return (missing_space);
}

void	delete_last_spaces(char **str)
{
	int		len;
	int		i;
	int	nb_space;
	char	*tmp;

	len = ft_strlen(*str) - 1;
	tmp = NULL;
	i = -1;
	nb_space = 0;
	while (is_w_space((*str)[len]))
	{
		nb_space++;
		len--;
	}
	if (nb_space)
	{
		tmp = malloc(sizeof(char) * (len + 2));
		if (!tmp)
			return ;
		while (i++ < len)
			tmp[i] = (*str)[i];
		tmp[i] = 0;
		free(*str);
		*str = ft_strdup(tmp);
		free(tmp);
	}
}

char	*pimp_my_string(t_mini *shell, int *sep)
{
	char	*ret;
	int		*ptr;
	int	i;
	int	j;

	i = 0;
	j = 0;
	ptr = sep;
	ret = (char *)malloc(sizeof(char) * (ft_strlen(shell->argv) + count_missing_space(shell->argv, sep) + 1));
	if (!ret)
		return (NULL);
	while (shell->argv[i])
	{
		ret[j++] = shell->argv[i++];
		if (is_sep(shell->argv[i]) && shell->argv[i] && i == *ptr)
		{
			if (!is_w_space(shell->argv[i - 1]))
				ret[j++] = 32;
		}
		else if (is_sep(shell->argv[i - 1]) && shell->argv[i] && (i - 1) == *ptr)
		{
			if (!is_w_space(shell->argv[i]))
				ret[j++] = 32;
			ptr++;
		}
	}
	ret[j] = 0;
	delete_last_spaces(&ret);
	free(shell->argv);
	return (ret);
}

int	count_nb_wrd(int *sep, int *space)
{
	int	i;

	i = 0;
	if (*sep == 0)
	{
		while (*space)
		{
			space++;
			i++;
		}
		return (i + 1);
	}
	else
	{
		while (*space < *sep)
		{
			i++;
			space++;
		}
		return (i);
	}
}

void	fill_array(t_mini *shell, int **sep, int **space, int *i)
{
	int	row;

	row = 0;
	if (**sep)
	{
		while (**space < **sep)
		{
			shell->current->args[row++] = ft_substr(shell->argv, *i, **space - *i);
			*i = **space;
			(*space)++;
			skip_w_space(shell->argv, i);
		}
		shell->current->args[row] = 0;
	}
	else
	{
		while (**space)
		{
			shell->current->args[row++] = ft_substr(shell->argv, *i, **space - *i);
			*i = **space;
			(*space)++;
			skip_w_space(shell->argv, i);
		}
		shell->current->args[row++] = ft_substr(shell->argv, *i, ft_strlen(shell->argv) - *i);
		shell->current->args[row] = 0;
	}
}

void	create_sep_node(t_mini *shell, int *i, int **space)
{
	shell->current->args = (char **)malloc(sizeof(char *) * 2);
	shell->current->args[0] = ft_substr(shell->argv, *i, **space - *i);
	shell->current->args[1] = 0;
	*i = **space;
	skip_w_space(shell->argv, i);
	(*space)++;
}

void	alloc_args_tab(t_mini *shell, int *sep, int *space)
{
	int	*ptr_sep;
	int	*ptr_space;
	int	i;

	ptr_sep = sep;
	ptr_space = space;
	i = 0;
	while (1)
	{
		shell->current->args = (char **)malloc(sizeof(char *) * (count_nb_wrd(ptr_sep, ptr_space) + 1));
		if (!shell->current->args)
			return ; //ERROR MALLOC CATCHED
		fill_array(shell, &ptr_sep, &ptr_space, &i);
		if (!(*ptr_sep))
			break ;
		shell->current = shell->current->next;
		if (is_sep(shell->argv[i]))
		{
			create_sep_node(shell, &i, &ptr_space);
			shell->current = shell->current->next;
		}
		ptr_sep++;
	}
}

int	detect_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 34 && str[i] != 39 && str[i])
		i++;
	if (str[i] == 34 || str[i] == 39)
		return (1);
	return (0);
}

void	delete_quote(t_mini *shell, int i, int *j)
{
	int		index;
	int		k;
	char	*ret;

	index = 0;
	k = 0;
	ret = malloc(sizeof(char) * ft_strlen(shell->current->args[i]) - 2);
	if (!ret)
		return ; // ERROR MALLOC
	while (shell->current->args[i][k])
	{
		if (k == *j)
			k++;
		if (shell->current->args[i][k] == shell->current->args[i][*j] && k > *j)
		{
			k++;
			*j = k - 2;
			break ;
		}
		ret[index] = shell->current->args[i][k];
		index++;
		k++;
	}
	while (shell->current->args[i][k])
	{
		ret[index] = shell->current->args[i][k];
		index++;
		k++;
	}
	ret[index] = 0;
	free(shell->current->args[i]);
	shell->current->args[i] = ft_strdup(ret);
	free(ret);
}

void	realloc_args(t_mini *shell, t_env **env_list, int j, int i)
{
	//ON SEST ARRETER LA AHGASGAGAGAGAGAGFFGAGAG

	char	*ret;

	ret = replace_dollars(shell->current->args[i], env_list, j + 1, 0);
	if (!ret)
		return ;
	free(shell->current->args[i]);
	shell->current->args[i] = ft_strdup(ret);
	free(ret);
}

void	quote_remover(t_mini *shell, t_env **env_list, int i)
{
	int	j;

	j = 0;
	while (shell->current->args[i][j])
	{
		if (shell->current->args[i][j] == 34)
		{
			if (have_a_dollar(shell->current->args[i], j + 1))
				realloc_args(shell, env_list, j, i);
			delete_quote(shell, i, &j);
		}
		if (shell->current->args[i][j] == 39)
		{
			delete_quote(shell, i, &j);
			j--;
		}
		j++;
	}
}

void	quotes_cleaner(t_mini *shell, t_env **env_list)
{
	int	i;

	while (shell->current && shell->current->next)
	{
		i = 0;
		while (shell->current->args[i])
		{
			if (detect_quote(shell->current->args[i]))
				quote_remover(shell, env_list, i);
			i++;
		}
		shell->current = shell->current->next;
	}
	i = 0;
	while (shell->current->args[i])
	{
		if (detect_quote(shell->current->args[i]))
			quote_remover(shell, env_list, i);
		i++;
	}
}

int	have_a_dollar_out_q(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			skip_quote(str, &i);
			i++;
		}
		else if (str[i] == '$')
			return (i);
		else
			i++;
	}
	return (-1);
}

int	realloc_string(t_mini *shell, int i, char *s2)
{
	free(shell->current->args[i]);
	shell->current->args[i] = NULL;
	shell->current->args[i] = ft_strdup(s2);
	free(s2);
	s2 = NULL;
	return (1);
}

void	dollar_out_quote(t_mini *shell, t_env **env_list)
{
	int	i;
	int	dollar_index;
	char *ret;

	while (shell->current)
	{
		i = 0;
		dollar_index = 0;
		while (shell->current->args[i])
		{
			dollar_index = have_a_dollar_out_q(shell->current->args[i]);
			if (dollar_index != -1)
			{
				ret = replace_dollars(shell->current->args[i], env_list, dollar_index, 1);
				realloc_string(shell, i, ret);
			}
			else
				i++; // le else permet de recheck une fois la string apres avoir traiter un premier dollar en dehors de quotes
			//genre si t'en a deux style echo salut$mama'salut'$mama
		}
		shell->current = shell->current->next;
	}
}

int	check_quote_err(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 34 || str[i] == 39)
		{
			skip_quote(str, &i);
			if (str[i] == '\0')
				return (print_quote_err());
		}
		i++;
	}
	return (0);
}

int	split_arg(t_mini *shell, t_env **env_list)
{
	//TODO : free int*
	int	*sep;
	int	*space;
	int	*ptr;
	(void)env_list;


	if (check_quote_err(shell->argv))
		return (0);
	sep = parse_sep(shell->argv);
	shell->argv = pimp_my_string(shell, sep);
	free(sep);
	sep = parse_sep(shell->argv);
	space = parse_space(shell->argv);
	init_args(shell);
	ptr = sep;
	while (*(ptr++))
	{
		create_n_add_empty_node(shell);
		create_n_add_empty_node(shell);
	}
	alloc_args_tab(shell, sep, space);
	shell->current = shell->first;
	dollar_out_quote(shell, env_list);
	shell->current = shell->first;
	quotes_cleaner(shell, env_list);
	shell->current = shell->first;
	return (1);
}

void	parsing(t_mini *shell, t_env **env_list)
{
	// Notre maniere d'appeler echo est mauvaise puisquil faut boucler lappel a echo pour le
	// nb darguments que notre node contient

	if (!ft_strcmp(shell->argv, ""))
		return ;
	if (!split_arg(shell, env_list))
		return ;
	shell->current = shell->first;
	if (!ft_strcmp(shell->first->args[0], EXPORT))
		export_func(env_list, shell->first->args[1]);
	else if (!ft_strcmp(shell->first->args[0], ECHO_CMD))
		echo_func(shell);
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
