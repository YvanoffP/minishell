#include "../../inc/minishell.h"

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

void	skip_quote(char *str, int *i)
{
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

int	str_error(char *str, int ret)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	return (ret);
}
