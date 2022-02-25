#include "../../inc/minishell.h"

void	create_sep_node(t_mini *shell, int *i, int **space)
{
	shell->current->args = (char **)malloc(sizeof(char *) * 2);
	shell->current->args[0] = ft_substr(shell->argv, *i, **space - *i);
	shell->current->args[1] = 0;
	*i = **space;
	skip_w_space(shell->argv, i);
	(*space)++;
}

void	realloc_args(t_mini *shell, t_env **env_list, int j, int i)
{
	char	*ret;

	ret = replace_dollars(shell->current->args[i], env_list, j + 1, 0);
	if (!ret)
		return ;
	free(shell->current->args[i]);
	shell->current->args[i] = ft_strdup(ret);
	free(ret);
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

int	realloc_string(t_mini *shell, int i, char *s2)
{
	free(shell->current->args[i]);
	shell->current->args[i] = NULL;
	shell->current->args[i] = ft_strdup(s2);
	free(s2);
	s2 = NULL;
	return (1);
}
