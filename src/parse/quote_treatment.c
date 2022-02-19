#include "../../inc/minishell.h"

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
				i++;
		}
		shell->current = shell->current->next;
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
