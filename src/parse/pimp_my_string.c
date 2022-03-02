#include "../../inc/minishell.h"

char	*check_around_n_cpy(t_mini *shell, int *ptr, int i, int j)
{
	char	*ret;

	skip_w_space(shell->argv, &i);
	ret = (char *)malloc(sizeof(char) * (ft_strlen(shell->argv) + count_missing_space(shell->argv, ptr - i) + 1));
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
		else if (is_sep(shell->argv[i - 1]) && shell->argv[i] && ((i - 1) == *ptr || (i - 2) == *ptr) && !is_sep(shell->argv[i]))
		{
			if (!is_w_space(shell->argv[i]))
				ret[j++] = 32;
			ptr++;
		}
	}
	ret[j] = 0;
	return (ret);
}

char	*pimp_my_string(t_mini *shell, int *sep)
{
	int		*ptr;
	char	*ret;

	ptr = sep;
	ret = check_around_n_cpy(shell, ptr, 0, 0);
	delete_last_spaces(&ret);
	free(shell->argv);
	return (ret);
}

void	work_nb_n_len(int *nb_space, int *len)
{
	*nb_space += 1;
	*len -= 1;
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
		work_nb_n_len(&nb_space, &len);
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
