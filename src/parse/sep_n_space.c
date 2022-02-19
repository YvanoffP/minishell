#include "../../inc/minishell.h"

int	count_sep(char *str)
{
	int	i;
	int	nb_sep;
	char	c;

	i = 0;
	nb_sep = 0;
	while (str[i])
	{
		skip_quote(str, &i);
		if (str[i] == '|' || str[i] == '<' || str[i] == '>')
		{
			nb_sep++;
			c = str[i];
			if (str[i + 1] == c && c != '|')
				i++;
			else if (is_sep(str[i + 1]))
				return (-1);
			if (is_sep(str[i + 1]))
				return (-1);
		}
		i++;
	}
	return (nb_sep);
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
	if (nb_sep == -1)
		return (NULL);
	ind_sep = malloc(sizeof(int) * nb_sep + 1);
	if (!ind_sep)
		return (NULL);
	while (str[i])
	{
		skip_quote(str, &i);
		if (is_sep(str[i]))
		{
			ind_sep[j++] = i;
			while (is_sep(str[i + 1]))
				i++;
		}
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
