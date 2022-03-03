#include "../../inc/minishell.h"

char	*delete_quote(char *str, int *j)
{
	int		index;
	int		k;
	char	*ret;

	index = 0;
	k = 0;
	ret = malloc(sizeof(char) * (ft_strlen(str) - 2));
	if (!ret)
		return (NULL);
	while (str[k])
	{
		if (k == *j)
			k++;
		if (str[k] == str[*j] && k > *j)
		{
			*j = k++ - 2;
			break ;
		}
		ret[index++] = str[k++];
	}
	while (str[k])
		ret[index++] = str[k++];
	ret[index] = 0;
	free(str);
	return (ret);
}

char	*quote_remover(char *str, t_env **env_list)
{
	char	*ret;
	int		j;

	j = 0;
	while (str[j])
	{
		if (str[j] == 34)
		{
			if (have_a_dollar(str, j + 1))
			{
				ret = replace_dollars(str, env_list, j + 1, 1);
				str = realloc_string(str, ret);
			}
			str = delete_quote(str, &j);
			if (str == NULL)
				return (str);
		}
		if (str[j] == 39)
		{
			str = delete_quote(str, &j);
			j--;
		}
		j++;
	}
	return (str);
}

void	quotes_cleaner(t_mini *shell, t_env **env_list)
{
	t_command		*child;
	t_built_args	*tmp;
	t_redir			*temp;

	child = shell->child;
	while (child)
	{
		tmp = child->args;
		temp = child->redirection;
		if (detect_quote(child->cmd))
			child->cmd = quote_remover(child->cmd, env_list);
		while (tmp)
		{
			if (detect_quote(tmp->name))
				tmp->name = quote_remover(tmp->name, env_list);
			tmp = tmp->next;
		}
		while (temp)
		{
			if (detect_quote(temp->file_name))
				temp->file_name = quote_remover(temp->file_name, env_list);
			temp = temp->next;
		}
		child = child->next;
	}
}

char	*realloc_string(char *str, char *s2)
{
	free(str);
	str = NULL;
	str = ft_strdup(s2);
	free(s2);
	s2 = NULL;
	return (str);
}
