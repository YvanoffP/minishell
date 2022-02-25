#include "../../inc/minishell.h"

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

int	check_args_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		skip_w_space(str, &i);
		if (is_sep(str[i]))
			return (1);
		while (!is_sep(str[i]) && str[i])
			i++;
		while (is_sep(str[i]) && str[i])
			i++;
	}
	if (is_sep(str[i - 1]))
		return (1);
	return (0);
}

int	str_error(char *str, int ret)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	return (ret);
}
